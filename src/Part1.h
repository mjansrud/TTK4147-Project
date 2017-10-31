#ifndef PART1_H_
#define PART1_H_

float get_y(struct udp_conn *connection);\
void regulator(struct udp_conn *connection, float reference);
void part_1_main(struct udp_conn *connection);

#endif /* PART1_H_ */
