#ifndef PART2_H_
#define PART2_H_

void ack_signal(struct udp_conn *connection);
void req_y(struct udp_conn *connection);
void *receiver(struct udp_conn *connection);
void *handler(struct udp_conn *connection);
void *controller(struct udp_conn *connection);
void part_2_main(struct udp_conn *connection);

#endif /* PART2_H_ */
