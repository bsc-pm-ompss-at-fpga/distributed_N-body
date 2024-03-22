# Distributed N-body

**Name**: N-Body Simulation  
**Contact Person**: OmpSs@FPGA Team, ompss-fpga-support@bsc.es  
**License Agreement**: GPL 3.0  
**Platform**: OmpSs@FPGA+IMP+OMPIF

## Description
N-body is a simulation of a dynamical system of particles, under the influence of gravitational forces.
For each pair of particles in the system, the force is calculated with the Newton's law of universal gravitation:
$$F_{ij}=\frac{G\times m_{i}\times m_{j}\times (p_{j}-p_{i})}{||p_{j}-p_{i}||^3}$$
$G$ is the gravitational constant $6.674×10^{-11} N⋅m^2/kg^2$, $p$ is the position 3-dimensional vector, $F$ is the force vector, and $m$ is the mass of a particle.

On every step, we have to calculate the force of every pair to every other pair of particles, and accumulate the force vector.
After this step, we have to update the positions and velocities of each particle according to the accumulated force.
For that, we use the Euler method assuming uniform acceleration between steps:
$$v_{t+1} = v_{t} + \frac{F_{t}}{m}d$$
$$p_{t+1} = p_{t} + v_{t}d + \frac{1}{2}\frac{F_{t}}{m}d^2$$

$v$ is the velocity vector, $d$ is the time between steps, and $t$ is the step.

## Parallelization with tasks

There are two types of tasks, force accumulation and particle update, that use the introduced formulas on blocks of a fixed size.
The force accumulation task takes as input two particle blocks, and one input/output force blocks.
Force blocks contain three different arrays with the x,y, and z components of the force vector.
Particle blocks contain an array for each property of a particle: x,y, and z components of the position and velocity vectors, mass and weight.
The weight is calculated as the mass multipled by the gravitational constant.
This is an optimization to avoid one multiplication in the update particle task, because te result of that multiplication is constant on each step of the simulation.

![nbody_task_proc](https://github.com/bsc-pm-ompss-at-fpga/distributed_N-body/assets/17345627/09d7645a-8f05-4789-a87c-625b47b3b068)

This image shows an example of the tasks created in one step with three blocks.
The force accumulation tasks are grouped by the force block they update, and the lines represent the input particle blocks.
Although there are 9 tasks, only 3 of them can be executed at the same time due to the out dependence on the force block.
Once all the force accumulation tasks finish for a force block, the update particle task can execute and update the positions and velocities of the block.

## Parallelization with Implicit Message Passing

The strategy shown in the previous sections needs a system with shared memory.
However, the implementation of this repo works on distributed memory systems, like in an MPI scenario.

With IMP, there are no calls to the message passing API (OMPIF in our case), which are called from a wrapper to the `mcxx_create_task` function in the `nbody_solve.cpp` file.
You will see this in the update particle task creation.
There is one data owner for the particle block, with a special owner -1.
This means the block is owned by everyone, so after the task finshes on the owner rank, it broadcasts the block to the rest of the cluster.
By doing this, after every step all ranks broadcast the particle block they updated.
We need to do this because even if every rank only calculates a subset of the forces, they need to read all the particles.

![nbody_imp_proc](https://github.com/bsc-pm-ompss-at-fpga/distributed_N-body/assets/17345627/00c9156d-6e57-420d-b856-17f0a8b641fb)

This image shows the same scenario in the previous section but distributing one block on a different rank with IMP.
We can see how after the particle update of the owned block, each rank sends its part to the others.

The OMPIF broadcast is slighlty different from the regular MPI counterpart.
It is a task that sends the same data to the rest of the cluster, but doesn't have a implicit barrier and must be executed only by the sender rank.
These are the green tasks of the image.
The other ranks must execute the corresponding OMPIF_Recv, which are the red tasks in the image.
However, this is taken care by the `mcxx_create_task` wrapper, and it is not visible by the user.

## How to compile

Sadly, there is no official support in the clang compiler for OMPIF and IMP, so we have to split manually the FPGA and the host part.
The host code is under `src`.
You will see an implementation of the `calculate_forces` and `update_particles` tasks, but that code is not actually used, it is there because the compiler for the host app still needs an implementation for those funcions.
In execution time, the code will search for the FPGA accelerators, which are implemented in the hls under the `hls` directory.

So, first you need an OmpSs@FPGA installation with broadcaster support for both in Nanos6 and clang.
Also, you need the AIT version that implements Ethernet subsystem and OMPIF support.
For the moment these versions are not official nor public, you can ask for access to ompss-fpga-support@bsc.es.

In summary, to compile the host executable run `make`
To generate the bitstream run `make ait`

There are some important variables in the Makefile:
- FPGA_CLOCK: frequency in MHz at which the accelerators will run.
- FPGA_MEMORY_PORT_WIDTH: Data bit-width of the memory port for all the accelerators. More bit-width may provide more bandwidth (depending on the FPGA memory path), at the cost of more resource usage.
- NBODY_BLOCK_SIZE: The number of elements assigned to a block. This determines the execution time of the accelerators, as well as the size of the accelerator internal memory.
- NBODY_NCALCFORCES: The number of forces calculated per cycle. The main loop of the force calculation is pipelined with II=1 and unrolled with a factor determined by this variable. The more parallel forces the more performance, but this greatly increases resource usage, specially DSPs, and also increases the number of ports of the internal memories.
- NBODY_NUM_FBLOCK_ACCS: Number of calculate forces block accelerators. Since this part is much more computationally expensive than the particle update, it is the only accelerator that we replicate. There is only 1 instance of the update accelerator. **IMPORTANT** If you want to change this variable, change the `num_instances` field of the `ait_extracted.json` file. Usually this file is generated by clang, but since we do not have that support with OMPIF or IMP, we have to modify the file manually.
