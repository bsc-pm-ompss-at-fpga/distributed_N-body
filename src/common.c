//
// This file is part of NBody and is licensed under the terms contained
// in the LICENSE file.
//
// Copyright (C) 2021 Barcelona Supercomputing Center (BSC)
//

#include "common.h"

#include <assert.h>
#include <getopt.h>
#include <ieee754.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>

void * nbody_alloc(size_t size)
{
	void *addr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	assert(addr != MAP_FAILED);
	return addr;
}

void nbody_print_usage(int argc, char **argv)
{
	fprintf(stderr, "Usage: %s <-p particles> <-t timesteps> [OPTION]...\n", argv[0]);
	fprintf(stderr, "Parameters:\n");
	fprintf(stderr, "  -p, --particles=PARTICLES\t\tuse PARTICLES as the total number of particles (default: 16384)\n");
	fprintf(stderr, "  -t, --timesteps=TIMESTEPS\t\tuse TIMESTEPS as the number of timesteps (default: 10)\n\n");
	fprintf(stderr, "Optional parameters:\n");
	fprintf(stderr, "  -f, --force-generation\t\t\t\talways force the generation of particles without the usage of files(disabled by default)\n");
	fprintf(stderr, "  -c, --check\t\t\t\tcheck the correctness of the result (disabled by default)\n");
	fprintf(stderr, "  -C, --no-check\t\t\tdo not check the correctness of the result\n");
	fprintf(stderr, "  -o, --output\t\t\t\tsave the computed particles to the default output file (disabled by default)\n");
	fprintf(stderr, "  -O, --no-output\t\t\tdo not save the computed particles to the default output file\n");
	fprintf(stderr, "  -P, --parse\t\t\t\tdisplay only the time in seconds\n");
	fprintf(stderr, "  -h, --help\t\t\t\tdisplay this help and exit\n\n");
}

nbody_conf_t nbody_get_conf(int *ok, int argc, char **argv)
{
	*ok = 1;
	nbody_conf_t conf;
	conf.domain_size_x    = default_domain_size_x;
	conf.domain_size_y    = default_domain_size_y;
	conf.domain_size_z    = default_domain_size_z;
	conf.mass_maximum     = default_mass_maximum;
	conf.time_interval    = default_time_interval;
	conf.seed             = default_seed;
	conf.name             = default_name;
	conf.num_particles    = default_num_particles;
	conf.num_blocks       = conf.num_particles / BLOCK_SIZE;
	conf.timesteps        = default_timesteps;
	conf.save_result      = default_save_result;
	conf.check_result     = default_check_result;
	conf.force_generation = default_force_generation;
	conf.parse            = 0;
	
	static struct option long_options[] = {
		{"particles",	required_argument,	0, 'p'},
		{"timesteps",	required_argument,	0, 't'},
		{"force-generation",		no_argument,		0, 'f'},
		{"check",		no_argument,		0, 'c'},
		{"no-check",	no_argument,		0, 'C'},
		{"output",		no_argument,		0, 'o'},
		{"no-output",	no_argument,		0, 'O'},
		{"parse", no_argument, 0, 'P'},
		{"help",		no_argument,		0, 'h'},
		{0, 0, 0, 0}
	};
	
	int c;
	int index;
	while ((c = getopt_long(argc, argv, "hfoOcCPp:t:", long_options, &index)) != -1) {
		switch (c) {
			case 'h':
				nbody_print_usage(argc, argv);
				exit(0);
			case 'f':
				conf.force_generation = 1;
				break;
			case 'o':
				conf.save_result = 1;
				break;
			case 'O':
				conf.save_result = 0;
				break;
			case 'c':
				conf.check_result = 1;
				break;
			case 'C':
				conf.check_result = 0;
				break;
			case 'P':
				conf.parse = 1;
				break;
			case 'p':
				conf.num_particles = atoi(optarg);
				break;
			case 't':
				conf.timesteps = atoi(optarg);
				break;
			case '?':
				*ok = 0;
				break;
			default:
				*ok = 0;
				break;
		}
	}
	
	if (!conf.num_particles || !conf.timesteps) {
		nbody_print_usage(argc, argv);
		*ok = 0;
	}
	
	return conf;
}

double nbody_compute_throughput(int num_particles, int timesteps, double elapsed_time)
{
	double interactions_per_timestep = 0;
#if defined(_BIGO_N2)
	interactions_per_timestep = (double)(num_particles)*(double)(num_particles);
#elif defined(_BIGO_NlogN)
	interactions_per_timestep = (double)(num_particles)*(double)(LOG2(num_particles));
#elif defined(_BIGO_N)
	interactions_per_timestep = (double)(num_particles);
#endif
	return (((interactions_per_timestep * (double)timesteps) / elapsed_time) / 1000000000.0);
}

double get_time()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (double)(ts.tv_sec) + (double)ts.tv_nsec * 1.0e-9;
}
