//
// This file is part of NBody and is licensed under the terms contained
// in the LICENSE file.
//
// Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
//

#include "nbody.h"

#include <ieee754.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>


void nbody_particle_init(const nbody_conf_t *conf, particles_block_t *part)
{
	for (int i = 0; i < BLOCK_SIZE; i++){
		part->position_x[i] = conf->domain_size_x * ((float)random() / ((float)RAND_MAX + 1.0));
		part->position_y[i] = conf->domain_size_y * ((float)random() / ((float)RAND_MAX + 1.0));
		part->position_z[i] = conf->domain_size_z * ((float)random() / ((float)RAND_MAX + 1.0));
		part->mass[i] = conf->mass_maximum * ((float)random() / ((float)RAND_MAX + 1.0));
		part->weight[i] = gravitational_constant * part->mass[i];
	}
}

int nbody_compare_particles(const particles_block_t *local, const particles_block_t *reference, int num_blocks)
{
	double error = 0.0;
	int count = 0;
	for (int i = 0; i < num_blocks; i++) {
		for (int e = 0; e < BLOCK_SIZE; e++) {
			if ((local[i].position_x[e] != reference[i].position_x[e]) ||
			    (local[i].position_y[e] != reference[i].position_y[e]) ||
			    (local[i].position_z[e] != reference[i].position_z[e])) {
				error += fabs(((local[i].position_x[e] - reference[i].position_x[e])*100.0) / reference[i].position_x[e]) +
				         fabs(((local[i].position_y[e] - reference[i].position_y[e])*100.0) / reference[i].position_y[e]) +
				         fabs(((local[i].position_z[e] - reference[i].position_z[e])*100.0) / reference[i].position_z[e]);
				count++;
				if (count <= 100) {
					typedef union {
						float t;
						unsigned int r;
					} cast_t;
					cast_t xref, yref, zref, x, y, z;
					xref.t = reference[i].position_x[e];
					yref.t = reference[i].position_y[e];
					zref.t = reference[i].position_z[e];
					x.t = local[i].position_x[e];
					y.t = local[i].position_y[e];
					z.t = local[i].position_z[e];
					printf("block %d pos %d: expected (%e %e %e) found (%e %e %e) %X %X %X   %X %X %X\n", i, e,
						reference[i].position_x[e], reference[i].position_y[e], reference[i].position_z[e],
						local[i].position_x[e], local[i].position_y[e], local[i].position_z[e], xref.r, yref.r, zref.r, x.r, y.r, z.r);
				}
			}
		}
	}
	
	double relative_error = (count != 0) ? error / (3.0 * count) : 0.0;
	printf("count %d relative error %g\n", count, relative_error);
	if ((count * 100.0) / (num_blocks * BLOCK_SIZE) > 60 || relative_error > TOLERATED_ERROR) {
		return 0;
	}
	return 1;
}

