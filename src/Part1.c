/*
 ============================================================================
 Name        : TTK4147-Project.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "Client.h"
#include "Shared.h"
#include "Part2.h"

struct timespec program_sleep;
float part_1_integral = 0.0;

float get_y(struct udp_conn *connection){

	char get_command[] = "GET";
	udp_send(connection, get_command, sizeof(get_command));

	char buffer[25];
	udp_receive(connection, buffer, sizeof(buffer)+1);

	return atof(buffer + sizeof("GET_ACK"));

}

void regulator(struct udp_conn *connection, float reference){

	float error = reference - get_y(connection);
	part_1_integral = part_1_integral + (error * SLEEP_PERIOD / MILLISEC_TO_SEC);
	float u = KP * error + KI * part_1_integral;

	set_u(u);

}

void part_1_main(struct udp_conn *connection){

	printf("----- TTK4147 Project ------ \n");
	printf("---------- PART 1 ---------- \n");

	clock_gettime(CLOCK_REALTIME, &program_sleep);

	int counter;
	int counter_goal = RUN_PERIOD/SLEEP_PERIOD;

	for (counter = 0; counter < counter_goal; counter++){
		regulator(connection, 1.0);
		timespec_add_us(&program_sleep, SLEEP_PERIOD);
		clock_nanosleep(&program_sleep);
	}

	printf("----- Stopping program ------ \n");
}
