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
#include "TTK4147-Project.h"
#include "Client.h"
#include <string.h>

//Variables
struct udp_conn connection;
char *ip = "192.168.0.1";

//Functions
void regulator(){


	float input  = 10;
	float kp  = 10;
	float ki  = 10;

	set_u(input);
	printf("Output %f \n", get_y());

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
	sprintf(str_input, "%s%d", set_command, input);

	udp_send(&connection, str_input, sizeof(set_command));

}

void start_server(){

	char start_command[] = "START";
	udp_send(&connection, start_command, sizeof(start_command));

}

void stop_server(){

	char stop_command[] = "STOP";
	udp_send(&connection, stop_command, sizeof(stop_command));

}

int main(void) {
	printf("----- TTK4147 Project ------ \n");

	udp_init_client(&connection, 9999, ip);
	start_server();

	printf("Starting PI Regulator \n");
	for(;;){
		regulator();
	}

	stop_server();
	udp_close(&connection);
	return EXIT_SUCCESS;
}
