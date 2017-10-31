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
#include "Part1.h"
#include "Shared.h"

struct timespec program_sleep;

void main_part_1(void) {

	printf("----- TTK4147 Project ------ \n");
	printf("---------- PART 1 ---------- \n");

	clock_gettime(CLOCK_REALTIME, &program_sleep);

	int counter;
	int counter_goal = RUN_PERIOD/SLEEP_PERIOD;

	for (counter = 0; counter < counter_goal; counter++){
		regulator(1.0);
		timespec_add_us(&program_sleep, SLEEP_PERIOD);
		clock_nanosleep(&program_sleep);
	}

	printf("----- Stopping program ------ \n");
}
