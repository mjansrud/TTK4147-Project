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
#include "Queue.h"
#include "Part2.h"

float part_2_integral = 0.0;

void ack_signal(struct udp_conn *connection){

	char get_command[] = "SIGNAL_ACK";
	udp_send(connection, get_command, sizeof(get_command));

}

void req_y(struct udp_conn *connection){

	char get_command[] = "GET";
	udp_send(connection, get_command, sizeof(get_command));

}

void *receiver(struct udp_conn *connection){
	printf("Starting receiver \n");

	char buffer[25];
	char type[6];

	for(;;){

		udp_receive(connection, buffer, sizeof(buffer)+1);
		strncpy(type, buffer, 6);

		if (!strncmp(buffer, "SIGNAL", 6)) {
			queue_add(SIGNAL, 0);
		}
		if (!strncmp(buffer, "GET_ACK", 7)) {
			queue_add(Y, atof(buffer + sizeof("GET_ACK")));
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

		if(queue.oldest && queue.oldest->type == Y){
			printf("LOlz \n");
			struct message* msg = queue_pop();
			printf("%f \n", msg->value);
			float error = reference - msg->value;
			printf("Woho, message %f \n", msg->value);
			part_2_integral = part_2_integral + (error * SLEEP_PERIOD / MILLISEC_TO_SEC);
			float u = KP * error + KI * part_2_integral;
			set_u(u);
		}

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

	// Make sure it can be shared across processes
	pthread_mutex_init(&queue_mutex, NULL);
	queue_init();

    pthread_t thread_receiver;
    pthread_t thread_controller;
    pthread_t thread_handler;

    pthread_create(&thread_receiver,  NULL, receiver, connection);
    pthread_create(&thread_controller, NULL, controller, connection);
    pthread_create(&thread_handler,   NULL, handler, connection);

    //Exit after counter
    pthread_join(thread_controller, NULL);

}
