#ifndef PART2_H_
#define PART2_H_

void ack_signal(struct udp_conn *connection);
void *receiver(struct udp_conn *connection);
void *acknowledger(struct udp_conn *connection);
void *controller(struct udp_conn *connection);
void part_2(struct udp_conn *connection);

#endif /* PART2_H_ */
