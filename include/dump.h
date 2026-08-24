#ifndef DUMP_H
#define DUMP_H

#include <pcap.h>
#include <stdlib.h>

void capture_live(const char *dev_name);
void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
void print_live(const u_char *data, int len);

#endif
