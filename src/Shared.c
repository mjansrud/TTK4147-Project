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
#include "Part1.h"
#include "Part2.h"

//Variables
struct udp_conn connection;
char *ip = IP;

void set_u(float input){

	char set_command[] = "SET:";

	char str_input[sizeof(set_command) + sizeof(input)];
	sprintf(str_input, "%s%f", set_command, input);

	udp_send(&connection, str_input, sizeof(str_input));
	printf("Output %f, input %f \n", get_y(&connection), input);

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
			part_1_main(&connection);
	}
	else if(!strcmp(argv[1], "-part2")) {
			part_2_main(&connection);
	}
	else{
		printf("Illegal argument, expected: -part1 or -part2 \n");
	}

	stop_server();
	udp_close(&connection);
	return EXIT_SUCCESS;

}
