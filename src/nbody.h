//
// This file is part of NBody and is licensed under the terms contained
// in the LICENSE file.
//
// Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
//

#ifndef NBODY_H
#define NBODY_H

#include "common.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

// Block size definition
#ifndef BLOCK_SIZE
#define BLOCK_SIZE 2048
#endif

#define MIN_PARTICLES (4096 * BLOCK_SIZE / sizeof(particles_block_t))

static const unsigned int NCALCFORCES = NBODY_NCALCFORCES;
static const unsigned int FPGA_PWIDTH = FPGA_MEMORY_PORT_WIDTH;
enum {
    FBLOCK_NUM_ACCS = NBODY_NUM_FBLOCK_ACCS,
    BLOCK_SIZE_C = BLOCK_SIZE
};

static const unsigned int PARTICLES_FPGABLOCK_POS_X_OFFSET  = 0*BLOCK_SIZE;
static const unsigned int PARTICLES_FPGABLOCK_POS_Y_OFFSET  = 1*BLOCK_SIZE;
static const unsigned int PARTICLES_FPGABLOCK_POS_Z_OFFSET  = 2*BLOCK_SIZE;
static const unsigned int PARTICLES_FPGABLOCK_VEL_X_OFFSET  = 3*BLOCK_SIZE;
static const unsigned int PARTICLES_FPGABLOCK_VEL_Y_OFFSET  = 4*BLOCK_SIZE;
static const unsigned int PARTICLES_FPGABLOCK_VEL_Z_OFFSET  = 5*BLOCK_SIZE;
static const unsigned int PARTICLES_FPGABLOCK_MASS_OFFSET   = 6*BLOCK_SIZE;
static const unsigned int PARTICLES_FPGABLOCK_WEIGHT_OFFSET = 7*BLOCK_SIZE;

enum {
    PARTICLES_FPGABLOCK_SIZE = 8*BLOCK_SIZE,
    FORCE_FPGABLOCK_SIZE     = 3*BLOCK_SIZE
};

static const unsigned int FORCE_FPGABLOCK_X_OFFSET = 0*BLOCK_SIZE;
static const unsigned int FORCE_FPGABLOCK_Y_OFFSET = 1*BLOCK_SIZE;
static const unsigned int FORCE_FPGABLOCK_Z_OFFSET = 2*BLOCK_SIZE;

// Solver structures
typedef struct {
	float position_x[BLOCK_SIZE]; /* m   */
	float position_y[BLOCK_SIZE]; /* m   */
	float position_z[BLOCK_SIZE]; /* m   */
	float velocity_x[BLOCK_SIZE]; /* m/s */
	float velocity_y[BLOCK_SIZE]; /* m/s */
	float velocity_z[BLOCK_SIZE]; /* m/s */
	float mass[BLOCK_SIZE];       /* kg  */
	float weight[BLOCK_SIZE];
} particles_block_t;

typedef struct {
	float x[BLOCK_SIZE]; /* x   */
	float y[BLOCK_SIZE]; /* y   */
	float z[BLOCK_SIZE]; /* z   */
} forces_block_t;

// Forward declaration
typedef struct nbody_file_t nbody_file_t;
typedef struct nbody_t nbody_t;

// Solver function
#pragma oss task device(smp) inout([PARTICLES_FPGABLOCK_SIZE*num_blocks]particles, [FORCE_FPGABLOCK_SIZE*num_blocks]forces)
void nbody_solve(float *particles, float *forces, const int num_blocks, const int timesteps, const float time_interval);

// Auxiliary functions
nbody_t nbody_setup(const nbody_conf_t *conf);
void nbody_particle_init(const nbody_conf_t *conf, particles_block_t *part);
void nbody_stats(const nbody_t *nbody, const nbody_conf_t *conf, double time);
void nbody_save_particles(const nbody_t *nbody);
void nbody_free(nbody_t *nbody);
void nbody_check(const nbody_t *nbody);
int nbody_compare_particles(const particles_block_t *local, const particles_block_t *reference, int num_blocks);

// Application structures
struct nbody_file_t {
        size_t size;
        char name[1000];
};

struct nbody_t {
        particles_block_t *particles;
        forces_block_t *forces;
        int num_blocks;
        int timesteps;
        nbody_file_t file;
};

#endif // NBODY_H

