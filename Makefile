# Compilers
CC = clang

# Nbody parameters
BS?=2048

PROGRAM_ = nbody

# FPGA bitstream parameters
FPGA_CLOCK             ?= 300
FPGA_MEMORY_PORT_WIDTH ?= 256
NBODY_BLOCK_SIZE       ?= 2048
NBODY_NCALCFORCES      ?= 8
NBODY_NUM_FBLOCK_ACCS  ?= 1
FROM_STEP ?= HLS

# Preprocessor flags
CPPFLAGS=-I$(NANOS6_HOME)/include -DBLOCK_SIZE=$(BS) -DNBODY_BLOCK_SIZE=$(NBODY_BLOCK_SIZE) -DNBODY_NCALCFORCES=$(NBODY_NCALCFORCES) -DNBODY_NUM_FBLOCK_ACCS=$(NBODY_NUM_FBLOCK_ACCS) -DFPGA_MEMORY_PORT_WIDTH=$(FPGA_MEMORY_PORT_WIDTH)

# Compiler flags
CFLAGS=-O3 -std=gnu11 -fompss-2

# Linker flags
LDFLAGS=-lrt -lm

SOURCES= \
    src/common.c \
    src/common_utils.c \
    src/utils.c \
    src/main.c \
    src/solver.c

PROGS= \
    nbody_ompss.$(BS).exe

nbody_ompss.$(BS).exe: $(SOURCES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

design:
	ait -b alveo_u55c -c $(FPGA_CLOCK) -n nbody -v --disable_board_support_check --wrapper_version 13 --disable_spawn_queues --placement_file u55c_placement_$(NBODY_NUM_FBLOCK_ACCS).json --floorplanning_constr all --slr_slices all --regslice_pipeline_stages 1:1:1 --enable_pom_axilite --max_deps_per_task=3 --max_args_per_task=11 --max_copies_per_task=11 --picos_tm_size=32 --picos_dm_size=102 --picos_vm_size=102 --interconnect_regslice all --to_step design --from_step $(FROM_STEP)

