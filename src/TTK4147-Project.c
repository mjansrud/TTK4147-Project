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

void regulator(){

	puts("Starting PI Regulator");

}

int main(void) {
	puts("!!!Hello World!!!");
	struct udp_conn connection;
	char ip = "191.168.01";
	udp_init_client(&connection, 9999, &ip);

	for(;;){


		puts("Running PI Regulator");
		usleep(100);
	}

	regulator();
	return EXIT_SUCCESS;
}
