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
#include <pthread.h>
#include <time.h>
#include <string.h>
#include "Client.h"
#include "Shared.h"
#include "Part2.h"

float part_2_integral = 0.0;
pthread_mutex_t mutex;

void ack_signal(struct udp_conn *connection){

	char get_command[] = "SIGNAL_ACK";
	pthread_mutex_lock(&mutex);
	udp_send(connection, get_command, sizeof(get_command));
    pthread_mutex_unlock(&mutex);

}

void req_y(struct udp_conn *connection){
	//printf("Requesting y \n");

	char get_command[] = "GET";
	pthread_mutex_lock(&mutex);
	udp_send(connection, get_command, sizeof(get_command));
    pthread_mutex_unlock(&mutex);

}

void *receiver(struct udp_conn *connection){
	printf("Starting receiver \n");

	char buffer[25];
	char type[6];

	for(;;){

		pthread_mutex_lock(&mutex);
		udp_receive(connection, buffer, sizeof(buffer)+1);
	    pthread_mutex_unlock(&mutex);

		strncpy(type, buffer, 6);

		if (!strncmp(buffer, "SIGNAL", 6)) {
			printf("SIGNAL \n");
		}
		if (!strncmp(buffer, "GET_ACK", 7)) {
			printf("ACH: %f \n",atof(buffer + sizeof("GET_ACH")));
		}

	}

}


void *controller(struct udp_conn *connection){
	printf("Starting controller \n");

	int counter;
	int reference = 1.0;
	int counter_goal = RUN_PERIOD/SLEEP_PERIOD;

	struct timespec program_sleep;
	clock_gettime(CLOCK_REALTIME, &program_sleep);

	for (counter = 0; counter < counter_goal; counter++){
		req_y(connection);

		/*
		float error = reference - get_signal(connection);
		part_2_integral = part_2_integral + (error * SLEEP_PERIOD / MILLISEC_TO_SEC);
		float u = KP * error + KI * part_2_integral;
		set_u(u);
		*/
		timespec_add_us(&program_sleep, SLEEP_PERIOD);
		clock_nanosleep(&program_sleep);
	}


}

void *handler(struct udp_conn *connection){
	printf("Starting handler \n");

}

void part_2_main(struct udp_conn *connection){

	printf("----- TTK4147 Project ------ \n");
	printf("---------- PART 2 ---------- \n");
	pthread_mutex_init(&mutex, NULL);

    pthread_t thread_receiver;
    pthread_t thread_controller;
    pthread_t thread_handler;

    pthread_create(&thread_receiver,  NULL, receiver, connection);
    pthread_create(&thread_controller, NULL, controller, connection);
    pthread_create(&thread_handler,   NULL, handler, connection);

    pthread_join(thread_receiver,  NULL);
    pthread_join(thread_controller, NULL);
    pthread_join(thread_handler, NULL);

}
