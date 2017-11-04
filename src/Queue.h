#ifndef QUEUE_H_
#define QUEUE_H_

struct queue queue;
pthread_mutex_t queue_mutex;

typedef enum {
	Y,
	SIGNAL,
} MESSAGE_TYPE;

struct message {
	MESSAGE_TYPE type;
	float value;
	struct Message* prev;
};

struct queue{
	struct message* newest;
	struct message* oldest;
};

#endif /* QUEUE_H_ */
