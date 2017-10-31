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
#include "Shared.h"
#include "Client.h"
#include <string.h>

//Variables
struct udp_conn connection;
float integral = 0.0;
char *ip = IP;

void regulator(float reference){

	float error = reference - get_y();
	integral = integral + (error * SLEEP_PERIOD / MILLISEC_TO_SEC);
	float u = KP * error + KI * integral;

	set_u(u);

}

float get_y(){

	char get_command[] = "GET";
	udp_send(&connection, get_command, sizeof(get_command));

	char buffer[25];
	udp_receive(&connection, buffer, sizeof(buffer)+1);

	return atof(buffer + sizeof("ACKOF: "));
}

void set_u(float input){

	char set_command[] = "SET:";

	char str_input[sizeof(set_command) + sizeof(input)];
	sprintf(str_input, "%s%f", set_command, input);

	udp_send(&connection, str_input, sizeof(str_input));
	//printf("Output %f, input %f, str_input %s \n", get_y(), input, str_input);

}

void start_server(){

	char start_command[] = "START";
	udp_send(&connection, start_command, sizeof(start_command));

}

void stop_server(){

	char stop_command[] = "STOP";
	udp_send(&connection, stop_command, sizeof(stop_command));

}

int main ( int argc, char *argv[] )
{

	udp_init_client(&connection, PORT, ip);
	start_server();

	if(!strcmp(argv[1], "-part1")) {
			main_part_1();
	}
	else if(!strcmp(argv[1], "-part2")) {
			main_part_2();
	}
	else{
		printf("Illegal argument, expected: -part1 or -part2 \n");
	}

	stop_server();
	udp_close(&connection);
	return EXIT_SUCCESS;

}
