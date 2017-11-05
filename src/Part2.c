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
#include <semaphore.h>
#include "Miniproject.h"
#include "Client.h"
#include "Part2.h"

float y;
sem_t sem_y;
sem_t sem_signal;
pthread_mutex_t mutex_y;

void part_2(struct udp_conn *connection){
	printf("---------- PART 2 ---------- \n");

	sem_init(&sem_y, 0, 1);
	sem_init(&sem_signal, 0, 1);
	pthread_mutex_init(&mutex_y, NULL);

    pthread_t thread_receiver;
    pthread_t thread_controller;
    pthread_t thread_acknowledger;

    pthread_create(&thread_receiver,  NULL, receiver, connection);
    pthread_create(&thread_controller, NULL, controller, connection);
    pthread_create(&thread_acknowledger,   NULL, acknowledger, connection);

    //Exit program when controller is finished
    pthread_join(thread_controller, NULL);

}

void *receiver(struct udp_conn *connection){
	printf("Starting receiver \n");

	char buffer[25];
	char type[6];

	for(;;){

		//Answering all messages from server
		udp_receive(connection, buffer, sizeof(buffer)+1);
		strncpy(type, buffer, 6);

		if (!strncmp(buffer, "SIGNAL", 6)) {
			sem_post(&sem_signal);
		}
		if (!strncmp(buffer, "GET_ACK", 7)) {
			pthread_mutex_lock(&mutex_y);
			y = atof(buffer + sizeof("GET_ACK"));
			pthread_mutex_unlock(&mutex_y);
			sem_post(&sem_y);
		}

	}

}

void *controller(struct udp_conn *connection){
	printf("Starting controller \n");

	int counter;
	int counter_goal = RUN_PERIOD/SLEEP_PERIOD;
	struct timespec program_sleep;
	clock_gettime(CLOCK_REALTIME, &program_sleep);

	for (counter = 0; counter < counter_goal; counter++){

		//Request new value and wait for response
		request_y(connection);
		sem_wait(&sem_y);

		pthread_mutex_lock(&mutex_y);
		set_u(get_u(y));
		pthread_mutex_unlock(&mutex_y);

		//Wait for new iteration
		timespec_add_us(&program_sleep, SLEEP_PERIOD);
		clock_nanosleep(&program_sleep);

	}
}

void *acknowledger(struct udp_conn *connection){
	printf("Starting acknowledger \n");

	for(;;){
		sem_wait(&sem_signal);
		char signal_command[] = "SIGNAL_ACK";
		send_message(signal_command, sizeof(signal_command));
	}

}
