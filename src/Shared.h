#ifndef SHARED_H_
#define SHARED_H_

float get_y();
void regulator(float reference);
void set_u(float input);
void start_server();
void stop_server();

//Timing
static const float MILLISEC_TO_SEC = 1000000.0;
static const int SLEEP_PERIOD = 2200;				//In microseconds
static const int RUN_PERIOD = 500000; 				//In microseconds

//Regulator
static const int KP = 10;
static const int KI = 800;

#define IP "192.168.0.1";
#define PORT 9999

#endif /* SHARED_H_ */
