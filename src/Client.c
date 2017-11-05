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
#include "Miniproject.h"
#include "Client.h"
#include "Part1.h"
#include "Part2.h"

//Variables
pthread_mutex_t mutex_sender;
struct udp_conn connection;
float integral = 0.0;
char *ip = IP;

int main ( int argc, char *argv[] ){

	printf("------ TTK4147 Project ------ \n");
	start_server();

	//Only one thread may send packets at the same time
	pthread_mutex_init(&mutex_sender, NULL);

	if(argv[1] == NULL){
		printf("Please choose -part1 or -part2 \n");
	}
	else if(!strcmp(argv[1], "-part1")) {
			part_1(&connection);
	}
	else if(!strcmp(argv[1], "-part2")) {
			part_2(&connection);
	}
	else{
		printf("Illegal argument, expected: -part1 or -part2 \n");
	}

	stop_server();
	printf("----- Stopping program ----- \n");
	return EXIT_SUCCESS;

}

/*
 *  Shared functions for part 1 and part 2
 */

void send_message(char *message, int length){

	pthread_mutex_lock(&mutex_sender);
	udp_send(&connection, message, length);
	pthread_mutex_unlock(&mutex_sender);

}

void start_server(){

	char start_command[] = "START";
	udp_init_client(&connection, PORT, ip);
	send_message(start_command, sizeof(start_command));

}

void stop_server(){

	char stop_command[] = "STOP";
	send_message(stop_command, sizeof(stop_command));
	udp_close(&connection);

}

void request_y(){

	char get_command[] = "GET";
	send_message(get_command, sizeof(get_command));

}

void set_u(float input){

	char set_command[] = "SET:";

	char str_input[sizeof(set_command) + sizeof(input)];
	sprintf(str_input, "%s%f", set_command, input);

	send_message(str_input, sizeof(str_input));

}

float get_u(float y){

	float error = reference - y;
	integral = integral + (error * SLEEP_PERIOD / MILLISEC_TO_SEC);
	return KP * error + KI * integral;

}
