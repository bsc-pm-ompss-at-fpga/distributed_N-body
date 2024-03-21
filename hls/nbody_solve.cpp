///////////////////
// Automatic IP Generated by OmpSs@FPGA compiler
///////////////////
// The below code is composed by:
//  1) User source code, which may be under any license (see in original source code)
//  2) OmpSs@FPGA toolchain code which is licensed under LGPLv3 terms and conditions
///////////////////
// Top IP Function: nbody_solve
// Accel. type hash: 6577428693
// Num. instances: 1
// Wrapper version: 13
///////////////////


#include <hls_stream.h>
#include <ap_int.h>
#include <ap_axi_sdata.h>

static ap_uint<64> __mcxx_taskId;
template<class T>
union __mcxx_cast {
   unsigned long long int raw;
   T typed;
};
struct mcxx_inaxis {
   ap_uint<64> data;
};

typedef ap_axiu<64, 1, 1, 2> mcxx_outaxis;

struct __fpga_copyinfo_t {
   unsigned long long int copy_address;
   unsigned char arg_idx;
   unsigned char flags;
   unsigned int size;
};
struct __data_owner_info_t {
	unsigned long long int size;
	unsigned char owner;
};
void mcxx_task_create(const ap_uint<64> type, const ap_uint<8> instanceNum, const ap_uint<8> numArgs, const unsigned long long int args[], const ap_uint<8> numDeps, const unsigned long long int deps[], const ap_uint<8> numCopies, const __fpga_copyinfo_t copies[], int numDataOwners, __data_owner_info_t data_owners[], hls::stream<mcxx_outaxis>& mcxx_outPort, unsigned char ompif_rank, unsigned char ompif_size, unsigned char owner);
void mcxx_task_create(const ap_uint<64> type, const ap_uint<8> instanceNum, const ap_uint<8> numArgs, const unsigned long long int args[], const ap_uint<8> numDeps, const unsigned long long int deps[], const ap_uint<8> numCopies, const __fpga_copyinfo_t copies[], hls::stream<mcxx_outaxis>& mcxx_outPort);
void mcxx_taskwait(hls::stream<ap_uint<8> >& mcxx_spawnInPort, hls::stream<mcxx_outaxis>& mcxx_outPort);
template <typename T>
struct __mcxx_ptr_t {
   unsigned long long int val;
   __mcxx_ptr_t(unsigned long long int val) : val(val) {}
   __mcxx_ptr_t() {}
   inline operator __mcxx_ptr_t<const T>() const {
      return __mcxx_ptr_t<const T>(val);
   }
   template <typename V> inline __mcxx_ptr_t<T> operator+(V const val) const {
      return __mcxx_ptr_t<T>(this->val + val*sizeof(T));
   }
   template <typename V> inline __mcxx_ptr_t<T> operator-(V const val) const {
      return __mcxx_ptr_t<T>(this->val - val*sizeof(T));
   }
   template <typename V> inline operator V() const {
      return (V)val;
   }
};
typedef enum {
   OMPIF_INT = 0,
   OMPIF_DOUBLE = 1,
   OMPIF_FLOAT = 2
} OMPIF_Datatype;
typedef enum {
   OMPIF_COMM_WORLD
} OMPIF_Comm;
void OMPIF_Send(const void *data, unsigned int size, int destination, const ap_uint<8> numDeps, const unsigned long long int deps[], hls::stream<mcxx_outaxis>& mcxx_outPort);
void OMPIF_Bcast(const void *data, unsigned int size, const ap_uint<8> numDeps, const unsigned long long int deps[], hls::stream<mcxx_outaxis>& mcxx_outPort);
void OMPIF_Recv(void *data, unsigned int size, int source, const ap_uint<8> numDeps, const unsigned long long int deps[], hls::stream<mcxx_outaxis>& mcxx_outPort);

static const unsigned int PARTICLES_FPGABLOCK_POS_X_OFFSET = 0 * 2048;
static const unsigned int PARTICLES_FPGABLOCK_POS_Y_OFFSET = 1 * 2048;
static const unsigned int PARTICLES_FPGABLOCK_POS_Z_OFFSET = 2 * 2048;
static const unsigned int PARTICLES_FPGABLOCK_MASS_OFFSET = 6 * 2048;
static const unsigned int PARTICLES_FPGABLOCK_WEIGHT_OFFSET = 7 * 2048;
static const unsigned int PARTICLES_FPGABLOCK_SIZE = 8 * 2048;
static const unsigned int FORCE_FPGABLOCK_X_OFFSET = 0 * 2048;
static const unsigned int FORCE_FPGABLOCK_Y_OFFSET = 1 * 2048;
static const unsigned int FORCE_FPGABLOCK_Z_OFFSET = 2 * 2048;
static const unsigned int FORCE_FPGABLOCK_SIZE = 3 * 2048;
static void update_particles_moved(__mcxx_ptr_t<float> particles, __mcxx_ptr_t<float> forces, const int num_blocks, const float time_interval, unsigned char __ompif_rank, unsigned char __ompif_size, hls::stream<mcxx_outaxis>& mcxx_outPort)
{
	const unsigned char cluster_size = __ompif_size;
	const int blocks_per_rank = num_blocks/cluster_size;
	update_particles:
	for (int i = 0; i < num_blocks; i++)
	{
		{
			unsigned long long int __mcxx_args[3L];
			unsigned long long int __mcxx_deps[2L];
			__fpga_copyinfo_t __mcxx_copies[2L];
			__mcxx_ptr_t<float> __mcxx_arg_0;
			__mcxx_arg_0 = particles + i * PARTICLES_FPGABLOCK_SIZE;
			__mcxx_args[0] = __mcxx_arg_0.val;
			const __fpga_copyinfo_t tmp_0 = {.copy_address = __mcxx_arg_0.val, .arg_idx = 0, .flags = 3, .size = 16384L * sizeof(float)};
			__mcxx_copies[0] = tmp_0;
			__mcxx_ptr_t<float> __mcxx_arg_1;
			__mcxx_arg_1 = forces + i * FORCE_FPGABLOCK_SIZE;
			__mcxx_args[1] = __mcxx_arg_1.val;
			const __fpga_copyinfo_t tmp_1 = {.copy_address = __mcxx_arg_1.val, .arg_idx = 1, .flags = 3, .size = 6144L * sizeof(float)};
			__mcxx_copies[1] = tmp_1;
			__mcxx_cast<float> cast_param_2;
			cast_param_2.typed = time_interval;
			__mcxx_args[2] = cast_param_2.raw;
			__mcxx_ptr_t<float> __mcxx_dep_0;
			__mcxx_dep_0 = particles + i * PARTICLES_FPGABLOCK_SIZE + 0L / 4U;
			__mcxx_deps[0] = 3LLU << 58 | __mcxx_dep_0.val;
			__mcxx_ptr_t<float> __mcxx_dep_1;
			__mcxx_dep_1 = forces + i * FORCE_FPGABLOCK_SIZE + 0L / 4U;
			__mcxx_deps[1] = 3LLU << 58 | __mcxx_dep_1.val;
			__data_owner_info_t data_owners[1];
			const __data_owner_info_t data_owner_0 = {.size = FORCE_FPGABLOCK_SIZE*sizeof(float), .owner = 255};
			data_owners[0] = data_owner_0;
			mcxx_task_create(4294967298LLU, 255, 3, __mcxx_args, 2, __mcxx_deps, 2, __mcxx_copies, 1, data_owners, mcxx_outPort, __ompif_rank, __ompif_size, i%cluster_size);
		}
		;
	}

}
static void calculate_forces_N2_moved(__mcxx_ptr_t<float> forces, __mcxx_ptr_t<const float> particles, const int num_blocks, unsigned char __ompif_rank, unsigned char __ompif_size, hls::stream<mcxx_outaxis>& mcxx_outPort)
{
#pragma HLS inline
	unsigned char cluster_size = __ompif_size;
	unsigned char cluster_rank = __ompif_rank;
	const unsigned int size = num_blocks/cluster_size;
	const int lower_bound = cluster_rank*size;
	const int upper_bound = cluster_rank*size + size;
	calc_forces_outer:
	for (int i = 0; i < num_blocks; i++)
	{
		calc_forces_inner:
		for (int j = 0; j < num_blocks; j++)
		{
#pragma HLS pipeline II=39 //3+11+3+11*2 calc_forces
			__mcxx_ptr_t<float> forcesTarget = forces + j * FORCE_FPGABLOCK_SIZE;
			__mcxx_ptr_t<const float> block1 = particles + j * PARTICLES_FPGABLOCK_SIZE;
			__mcxx_ptr_t<const float> block2 = particles + i * PARTICLES_FPGABLOCK_SIZE;
			{
				unsigned long long int __mcxx_args[11L];
				unsigned long long int __mcxx_deps[3L];
				__fpga_copyinfo_t __mcxx_copies[11L];
				__mcxx_ptr_t<float> __mcxx_arg_0;
				__mcxx_arg_0 = forcesTarget + FORCE_FPGABLOCK_X_OFFSET;
				__mcxx_args[0] = __mcxx_arg_0.val;
				const __fpga_copyinfo_t copy1 = {.copy_address = 0, .flags = 3, .arg_idx = 0, .size = 0};
				__mcxx_copies[0] = copy1;
				__mcxx_ptr_t<float> __mcxx_arg_1;
				__mcxx_arg_1 = forcesTarget + FORCE_FPGABLOCK_Y_OFFSET;
				__mcxx_args[1] = __mcxx_arg_1.val;
				const __fpga_copyinfo_t copy2 = {.copy_address = 0, .flags = 3, .arg_idx = 1, .size = 0};
				__mcxx_copies[1] = copy2;
				__mcxx_ptr_t<float> __mcxx_arg_2;
				__mcxx_arg_2 = forcesTarget + FORCE_FPGABLOCK_Z_OFFSET;
				__mcxx_args[2] = __mcxx_arg_2.val;
				const __fpga_copyinfo_t copy3 = {.copy_address = 0, .flags = 3, .arg_idx = 2, .size = 0};
				__mcxx_copies[2] = copy3;
				__mcxx_ptr_t<float> __mcxx_arg_3;
				__mcxx_arg_3 = block1 + PARTICLES_FPGABLOCK_POS_X_OFFSET;
				__mcxx_args[3] = __mcxx_arg_3.val;
				const __fpga_copyinfo_t copy4 = {.copy_address = 0, .flags = 1, .arg_idx = 3, .size = 0};
				__mcxx_copies[3] = copy4;
				__mcxx_ptr_t<float> __mcxx_arg_4;
				__mcxx_arg_4 = block1 + PARTICLES_FPGABLOCK_POS_Y_OFFSET;
				__mcxx_args[4] = __mcxx_arg_4.val;
				const __fpga_copyinfo_t copy5 = {.copy_address = 0, .flags = 1, .arg_idx = 4, .size = 0};
				__mcxx_copies[4] = copy5;
				__mcxx_ptr_t<float> __mcxx_arg_5;
				__mcxx_arg_5 = block1 + PARTICLES_FPGABLOCK_POS_Z_OFFSET;
				__mcxx_args[5] = __mcxx_arg_5.val;
				const __fpga_copyinfo_t copy6 = {.copy_address = 0, .flags = 1, .arg_idx = 5, .size = 0};
				__mcxx_copies[5] = copy6;
				__mcxx_ptr_t<float> __mcxx_arg_6;
				__mcxx_arg_6 = block1 + PARTICLES_FPGABLOCK_MASS_OFFSET;
				__mcxx_args[6] = __mcxx_arg_6.val;
				const __fpga_copyinfo_t copy7 = {.copy_address = 0, .flags = 1, .arg_idx = 6, .size = 0};
				__mcxx_copies[6] = copy7;
				__mcxx_ptr_t<float> __mcxx_arg_7;
				__mcxx_arg_7 = block2 + PARTICLES_FPGABLOCK_POS_X_OFFSET;
				__mcxx_args[7] = __mcxx_arg_7.val;
				const __fpga_copyinfo_t copy8 = {.copy_address = 0, .flags = 1, .arg_idx = 7, .size = 0};
				__mcxx_copies[7] = copy8;
				__mcxx_ptr_t<float> __mcxx_arg_8;
				__mcxx_arg_8 = block2 + PARTICLES_FPGABLOCK_POS_Y_OFFSET;
				__mcxx_args[8] = __mcxx_arg_8.val;
				const __fpga_copyinfo_t copy9 = {.copy_address = 0, .flags = 1, .arg_idx = 8, .size = 0};
				__mcxx_copies[8] = copy9;
				__mcxx_ptr_t<float> __mcxx_arg_9;
				__mcxx_arg_9 = block2 + PARTICLES_FPGABLOCK_POS_Z_OFFSET;
				__mcxx_args[9] = __mcxx_arg_9.val;
				const __fpga_copyinfo_t copy10 = {.copy_address = 0, .flags = 1, .arg_idx = 9, .size = 0};
				__mcxx_copies[9] = copy10;
				__mcxx_ptr_t<float> __mcxx_arg_10;
				__mcxx_arg_10 = block2 + PARTICLES_FPGABLOCK_WEIGHT_OFFSET;
				__mcxx_args[10] = __mcxx_arg_10.val;
				const __fpga_copyinfo_t copy11 = {.copy_address = 0, .flags = 1, .arg_idx = 10, .size = 0};
				__mcxx_copies[10] = copy11;
				__mcxx_ptr_t<float> __mcxx_dep_0;
				__mcxx_dep_0 = block2;
				__mcxx_deps[0] = 1LLU << 58 | __mcxx_dep_0.val;
				__mcxx_ptr_t<float> __mcxx_dep_1;
				__mcxx_dep_1 = block1;
				__mcxx_deps[1] = 1LLU << 58 | __mcxx_dep_1.val;
				__mcxx_ptr_t<float> __mcxx_dep_2;
				__mcxx_dep_2 = forcesTarget;
				__mcxx_deps[2] = 3LLU << 58 | __mcxx_dep_2.val;

				mcxx_task_create(4294967297LLU, 255, 11, __mcxx_args, 3, __mcxx_deps, 11, __mcxx_copies, 0, 0, mcxx_outPort, __ompif_rank, __ompif_size, j%cluster_size);
			}
			;
		}
	}
}
typedef unsigned char __uint8_t;
typedef __uint8_t uint8_t;
void nbody_solve_moved(__mcxx_ptr_t<float> particles, __mcxx_ptr_t<float> forces, const int num_blocks, const int timesteps, const float time_interval, unsigned char __ompif_rank, unsigned char __ompif_size, hls::stream<ap_uint<8> >& mcxx_spawnInPort, hls::stream<mcxx_outaxis>& mcxx_outPort)
{
#pragma HLS inline
  for (int t = 0; t < timesteps; t++)
    {
      calculate_forces_N2_moved(forces, particles, num_blocks, __ompif_rank, __ompif_size, mcxx_outPort);
      update_particles_moved(particles, forces, num_blocks, time_interval, __ompif_rank, __ompif_size, mcxx_outPort);
    }
  mcxx_taskwait(mcxx_spawnInPort, mcxx_outPort);
}

void mcxx_write_out_port(const ap_uint<64> data, const ap_uint<2> dest, const ap_uint<1> last, hls::stream<mcxx_outaxis>& mcxx_outPort) {
#pragma HLS inline
   mcxx_outaxis axis_word;
   axis_word.data = data;
   axis_word.dest = dest;
   axis_word.last = last;
   mcxx_outPort.write(axis_word);
}
void nbody_solve_wrapper(hls::stream<ap_uint<64> >& mcxx_inPort, hls::stream<mcxx_outaxis>& mcxx_outPort, hls::stream<ap_uint<8> >& mcxx_spawnInPort, unsigned char ompif_rank, unsigned char ompif_size) {
#pragma HLS interface ap_ctrl_none port=return
#pragma HLS interface axis port=mcxx_inPort
#pragma HLS interface axis port=mcxx_outPort
#pragma HLS interface axis port=mcxx_spawnInPort
#pragma HLS stable variable=ompif_rank
#pragma HLS stable variable=ompif_size
   mcxx_inPort.read(); //command word
   __mcxx_taskId = mcxx_inPort.read();
   ap_uint<64> __mcxx_parent_taskId = mcxx_inPort.read();
   __mcxx_ptr_t<float> particles;
   __mcxx_ptr_t<float> forces;
   int num_blocks;
   int timesteps;
   float time_interval;
   {
      #pragma HLS protocol fixed
      {
         ap_uint<8> mcxx_flags_0;
         ap_uint<64> mcxx_offset_0;
         mcxx_flags_0 = mcxx_inPort.read()(7,0);
         ap_wait();
         mcxx_offset_0 = mcxx_inPort.read();
         particles.val = mcxx_offset_0;
      }
      ap_wait();
      {
         ap_uint<8> mcxx_flags_1;
         ap_uint<64> mcxx_offset_1;
         mcxx_flags_1 = mcxx_inPort.read()(7,0);
         ap_wait();
         mcxx_offset_1 = mcxx_inPort.read();
         forces.val = mcxx_offset_1;
      }
      ap_wait();
      {
         ap_uint<8> mcxx_flags_2;
         ap_uint<64> mcxx_offset_2;
         mcxx_flags_2 = mcxx_inPort.read()(7,0);
         ap_wait();
         __mcxx_cast<int> mcxx_arg_2;
         mcxx_arg_2.raw = mcxx_inPort.read();
         num_blocks = mcxx_arg_2.typed;
      }
      ap_wait();
      {
         ap_uint<8> mcxx_flags_3;
         ap_uint<64> mcxx_offset_3;
         mcxx_flags_3 = mcxx_inPort.read()(7,0);
         ap_wait();
         __mcxx_cast<int> mcxx_arg_3;
         mcxx_arg_3.raw = mcxx_inPort.read();
         timesteps = mcxx_arg_3.typed;
      }
      ap_wait();
      {
         ap_uint<8> mcxx_flags_4;
         ap_uint<64> mcxx_offset_4;
         mcxx_flags_4 = mcxx_inPort.read()(7,0);
         ap_wait();
         __mcxx_cast<float> mcxx_arg_4;
         mcxx_arg_4.raw = mcxx_inPort.read();
         time_interval = mcxx_arg_4.typed;
      }
      ap_wait();
   }
   nbody_solve_moved(particles, forces, num_blocks, timesteps, time_interval, ompif_rank, ompif_size, mcxx_spawnInPort, mcxx_outPort);
   {
      #pragma HLS protocol fixed
      ap_uint<64> header = 0x03;
      ap_wait();
      mcxx_write_out_port(header, 0, 0, mcxx_outPort);
      ap_wait();
      mcxx_write_out_port(__mcxx_taskId, 0, 0, mcxx_outPort);
      ap_wait();
      mcxx_write_out_port(__mcxx_parent_taskId, 0, 1, mcxx_outPort);
      ap_wait();
   }
}

void mcxx_task_create(const ap_uint<64> type, const ap_uint<8> instanceNum, const ap_uint<8> numArgs, const unsigned long long int args[], const ap_uint<8> numDeps, const unsigned long long int deps[], const ap_uint<8> numCopies, const __fpga_copyinfo_t copies[], int numDataOwners, __data_owner_info_t data_owners[], hls::stream<mcxx_outaxis>& mcxx_outPort, unsigned char ompif_rank, unsigned char ompif_size, unsigned char owner) {
#pragma HLS inline
	const ap_uint<2> destId = 2;
	const unsigned char rank = ompif_rank;

	/*auto_sendrecv:
	for (ap_uint<4> i = 0; i < numDataOwners; ++i) {
		const unsigned char data_owner = data_owners[i].owner;
		const unsigned int size = data_owners[i].size;
		if (owner != rank && data_owners[i].owner == rank) {
			const unsigned long long addr = deps[i] & 0x00FFFFFFFFFFFFFF;
			const unsigned long long int dep[2] = {addr | (1LLU << 58), 0x0000100000000000LLU | (3LLU << 58)};
			OMPIF_Send((void*)addr, size, owner, 2, dep, mcxx_outPort);
		}
		else if (owner == rank && data_owner != rank) {
			const unsigned long long addr = deps[i] & 0x00FFFFFFFFFFFFFF;
			const unsigned long long int dep[2] = {addr | (2LLU << 58), 0x0000200000000000LLU | (3LLU << 58)};
			OMPIF_Recv((void*)addr, size, data_owner, 2, dep, mcxx_outPort);
		}
	}*/

	if (owner == rank) {
		mcxx_task_create(type, instanceNum, numArgs, args, numDeps, deps, numCopies, copies, mcxx_outPort);
	}

	for (ap_uint<4> i = 0; i < numDataOwners; ++i) {
#pragma HLS unroll
		const unsigned char data_owner = data_owners[i].owner;
		const unsigned int size = data_owners[i].size;
		const bool is_out = (deps[i] >> 59) & 0x1;
		if (owner == rank && data_owner == 255 && is_out) { //broadcast
			const unsigned long long addr = deps[i] & 0x00FFFFFFFFFFFFFF;
			const unsigned long long int dep[2] = {addr | (1LLU << 58), 0x0000100000000000LLU | (3LLU << 58)};
			unsigned char j = rank + 1 == ompif_size ? 0 : rank+1;
			OMPIF_Bcast((void*)addr, size, 2, dep, mcxx_outPort);
		}
		else if (owner != rank && data_owner == 255 && is_out) {
			const unsigned long long addr = deps[i] & 0x00FFFFFFFFFFFFFF;
			const unsigned long long int dep[2] = {addr | (2LLU << 58), 0x0000200000000000LLU | (3LLU << 58)};
			OMPIF_Recv((void*)addr, size, owner, 2, dep, mcxx_outPort);
		}
	}
}


void mcxx_task_create(const ap_uint<64> type, const ap_uint<8> instanceNum, const ap_uint<8> numArgs, const unsigned long long int args[], const ap_uint<8> numDeps, const unsigned long long int deps[], const ap_uint<8> numCopies, const __fpga_copyinfo_t copies[], hls::stream<mcxx_outaxis>& mcxx_outPort) {
#pragma HLS inline
   const ap_uint<2> destId = 2;
   ap_uint<64> tmp;
   tmp(15,8)  = numArgs;
   tmp(23,16) = numDeps;
   tmp(31,24) = numCopies;
   mcxx_write_out_port(tmp, destId, 0, mcxx_outPort);
   mcxx_write_out_port(__mcxx_taskId, destId, 0, mcxx_outPort);
   tmp(47,40) = instanceNum;
   tmp(33,0)  = type(33,0);
   mcxx_write_out_port(tmp, destId, 0, mcxx_outPort);
   for (ap_uint<4> i = 0; i < numDeps(3,0); ++i) {
      mcxx_write_out_port(deps[i], destId, numArgs == 0 && numCopies == 0 && i == numDeps-1, mcxx_outPort);
   }
   for (ap_uint<4> i = 0; i < numCopies(3,0); ++i) {
      mcxx_write_out_port(copies[i].copy_address, destId, 0, mcxx_outPort);
      tmp(7,0) = copies[i].flags;
      tmp(15,8) = copies[i].arg_idx;
      tmp(63,32) = copies[i].size;
      mcxx_write_out_port(tmp, destId, numArgs == 0 && i == numCopies-1, mcxx_outPort);
   }
   for (ap_uint<4> i = 0; i < numArgs(3,0); ++i) {
      mcxx_write_out_port(args[i], destId, i == numArgs-1, mcxx_outPort);
   }
}

void mcxx_taskwait(hls::stream<ap_uint<8> >& mcxx_spawnInPort, hls::stream<mcxx_outaxis>& mcxx_outPort) {
#pragma HLS inline
   ap_wait();
   mcxx_write_out_port(__mcxx_taskId, 3, 1, mcxx_outPort);
   ap_wait();
   mcxx_spawnInPort.read();
   ap_wait();
}

void OMPIF_Recv(void *data, unsigned int size, int source, const ap_uint<8> numDeps, const unsigned long long int deps[], hls::stream<mcxx_outaxis>& mcxx_outPort) {
#pragma HLS inline
	ap_uint<64> command;
	command(7,0) = 0; //RECV
	command(15,8) = 0;
	command(23,16) = source;
	command(63, 24) = (unsigned long long int)data;
	unsigned long long int args[2] = {command, (unsigned long long int)size};
	mcxx_task_create(4294967300LU, 0xFF, 2, args, numDeps, deps, 0, 0, mcxx_outPort);
}

void OMPIF_Bcast(const void *data, unsigned int size, const ap_uint<8> numDeps, const unsigned long long int deps[], hls::stream<mcxx_outaxis>& mcxx_outPort) {
#pragma HLS inline
	ap_uint<64> command;
	command(7,0) = 1; //SENDALL
	command(15,8) = 0;
	command(63, 24) = (unsigned long long int)data;
	unsigned long long int args[2] = {command, (unsigned long long int)size};
	mcxx_task_create(4294967299LU, 0xFF, 2, args, numDeps, deps, 0, 0, mcxx_outPort);
}

