//
// This file is part of NBody and is licensed under the terms contained
// in the LICENSE file.
//
// Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
//

#include "nbody.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <nanos6/distributed.h>

int main(int argc, char** argv)
{
	int ok;
	nbody_conf_t conf = nbody_get_conf(&ok, argc, argv);
	if (!ok) {
		return 1;
	}

	int devices = nanos6_dist_num_devices();
	if (devices <= 0) {
		fprintf(stderr, "Invalid number of devices %d\n", devices);
		return 1;
	}
	if (conf.num_particles%(BLOCK_SIZE*devices) != 0) {
		fprintf(stderr, "Number of particles not multiple of block size and number of devices\n");
		return 1;
	}

	assert(conf.num_particles >= BLOCK_SIZE);
	assert(conf.timesteps > 0);
	
	conf.num_blocks = conf.num_particles / BLOCK_SIZE;
	assert(conf.num_blocks > 0);
	
	nbody_t nbody = nbody_setup(&conf);
	
	particles_block_t *particles = nbody.particles;
	forces_block_t *forces = nbody.forces;

	nanos6_dist_map_address(particles, sizeof(particles_block_t)*conf.num_blocks);
	nanos6_dist_map_address(forces, sizeof(forces_block_t)*conf.num_blocks);

	double copy_start = get_time();
	int blocks_per_dev = conf.num_blocks/devices;
	nanos6_dist_memcpy_to_all(particles, sizeof(particles_block_t)*conf.num_blocks, 0, 0);
	nanos6_dist_memcpy_to_all(forces, sizeof(forces_block_t)*conf.num_blocks, 0, 0);
	double copy_end = get_time();
	double copy_time = copy_end-copy_start;
	double bandwidth = ((sizeof(particles_block_t)*conf.num_blocks+sizeof(forces_block_t)*conf.num_blocks)*devices)/copy_time;
	fprintf(stderr, "Copy time %fs bandwidth %.2fMB/s\n", copy_time, bandwidth/1024/1024);

	double start = get_time();
	nbody_solve((float*)particles, (float*)forces, conf.num_blocks, conf.timesteps, conf.time_interval);
	#pragma oss taskwait
	double end = get_time();

	if (conf.check_result) {
		for (int i = 0; i < devices; ++i) {
			nanos6_dist_memcpy_from_device(i, particles, sizeof(particles_block_t)*blocks_per_dev, sizeof(particles_block_t)*blocks_per_dev*i, sizeof(particles_block_t)*blocks_per_dev*i);
		}
	}

	nanos6_dist_unmap_address(particles);
	nanos6_dist_unmap_address(forces);
	
	nbody_stats(&nbody, &conf, end - start);
	
	if (conf.save_result && !conf.force_generation) nbody_save_particles(&nbody);
	if (conf.check_result) nbody_check(&nbody);
	nbody_free(&nbody);
	return 0;
}
