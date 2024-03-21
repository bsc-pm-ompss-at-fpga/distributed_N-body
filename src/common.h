//
// This file is part of NBody and is licensed under the terms contained
// in the LICENSE file.
//
// Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
//

#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

#define PART 1024
#define PAGE_SIZE 4096

#define TOLERATED_ERROR 0.0008

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define LOG2(a) (31-__builtin_clz((a)))
#define MOD(a, b)  ((a) < 0 ? ((((a) % (b)) + (b)) % (b)) : ((a) % (b)))
#define ROUNDUP(x, y) ({             \
    const typeof(y) __y = y;         \
    (((x) + (__y - 1)) / __y) * __y; \
})

static const float gravitational_constant   = 6.6726e-11f; /* N(m/kg)2 */
static const float default_domain_size_x    = 1.0e+10; /* m  */
static const float default_domain_size_y    = 1.0e+10; /* m  */
static const float default_domain_size_z    = 1.0e+10; /* m  */
static const float default_mass_maximum     = 1.0e+28; /* kg */
static const float default_time_interval    = 1.0e+0;  /* s  */
static const int   default_seed             = 12345;
static const char* default_name             = "data/nbody";
static const int   default_num_particles    = 0;
static const int   default_timesteps        = 0;
static const int   default_save_result      = 0;
static const int   default_check_result     = 0;
static const int   default_force_generation = 0;

typedef struct {
	float domain_size_x;
	float domain_size_y;
	float domain_size_z;
	float mass_maximum;
	float time_interval;
	int seed;
	const char* name;
	int num_particles;
	int num_blocks;
	int timesteps;
	int save_result;
	int check_result;
	int force_generation;
	char parse;
} nbody_conf_t;

nbody_conf_t nbody_get_conf(int* ok, int argc, char **argv);
double nbody_compute_throughput(int num_particles, int timesteps, double elapsed_time);
void * nbody_alloc(size_t size);
double get_time();

#endif // COMMON_H
