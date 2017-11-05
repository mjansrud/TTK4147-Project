/*
 ============================================================================
 Name        : Part1.c
 Author      : Morten Jansrud & Øystein Brox
 Version     : 99992.903.141
 Copyright   : Kjør på!
 Description : Simulation of a dynamical system in real-time that must be controlled - Part 1
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "Miniproject.h"
#include "Client.h"
#include "Part1.h"

struct timespec program_sleep;

void part_1(struct udp_conn *connection){
	printf("---------- PART 1 ---------- \n");

	int counter;
	int counter_goal = RUN_PERIOD/SLEEP_PERIOD;
	clock_gettime(CLOCK_REALTIME, &program_sleep);

	for (counter = 0; counter < counter_goal; counter++){

		//Controller
		set_u(get_u(get_y(connection)));

		//Wait for new iteration
		timespec_add_us(&program_sleep, SLEEP_PERIOD);
		clock_nanosleep(&program_sleep);

	}
}

// Only function unique for part 1
float get_y(struct udp_conn *connection){

	request_y();

	char buffer[25];
	udp_receive(connection, buffer, sizeof(buffer)+1);

	return atof(buffer + sizeof("GET_ACK"));

}



