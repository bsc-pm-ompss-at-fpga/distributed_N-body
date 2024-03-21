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

$v$ is the velocity vector, and $d$ is the time between steps.
