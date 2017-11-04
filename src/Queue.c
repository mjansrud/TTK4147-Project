#include <stddef.h>
#include <pthread.h>
#include "Queue.h";


void queue_init(){

	queue.newest = NULL;
	queue.oldest = NULL;

}

void queue_add(MESSAGE_TYPE type, float value){

	struct message msg;
	msg.type = type;
	msg.value = value;
	msg.prev = NULL;

    pthread_mutex_lock(&queue_mutex);

    if(!queue.oldest){
    	queue.oldest = &msg;
    }
    if(queue.newest){
    	queue.newest->prev = &msg;
    }
    queue.newest = &msg;

   pthread_mutex_unlock(&queue_mutex);
   queue_print();

}

struct message* queue_pop(){

 	 struct message* tmp = NULL;
	 if(queue.oldest){
		 pthread_mutex_lock(&queue_mutex);
		 tmp = queue.oldest;
		 queue.oldest = queue.oldest->prev;
		 pthread_mutex_unlock(&queue_mutex);
	 }
 	 return tmp;

}

void queue_print(){

	struct message* current = queue.oldest;

	while(current){
		printf("Message, type: %d, content: %f \n", current->type, current->value);

		if(current->prev){
			current = current->prev;
		}
	}
}

