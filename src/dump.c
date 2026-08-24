
/* pcap_open_live()  //find device */
/* pcap_lookupnet()  //get IP and net mask */
/* pcap_dump_open()  //open savefile */
/* pcap_dispatch()   //capture packets & call &pcap_dump */
/* pcap_stats()      //output capture stats to screen */
/* pcap_dump_close() //close file */
/* pcap_close()      //close device & free memory */

#include <stdio.h>
#include <pcap.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
  
#define SNAP_LEN 65535  
#define PROMISC 0       
#define TIMEOUT_MS 1000

void print_hex_ascii(const u_char *data, int len) {  
  for (int i = 0; i < len; i += 16) {
    printf("%04x  ", i);

    for (int j = 0; j < 16; j++) {
      if (i + j < len)
        printf("%02x ", data[i + j]);
      else
        printf("   ");
    }

    printf(" ");

    for (int j = 0; j < 16 && i + j < len; j++) {
      unsigned char c = data[i + j];
      printf("%c", (c >= 32 && c <= 126) ? c : '.');
    }
    printf("\n");
  }
}

/* void print_live(const u_char *data, int len){ */
/*   for (int i = 0; i < len; i++){ */
/*     printf("%02x", data[i]); */
/*     if ((i + 1) % 16 == 0) printf("\n"); */
/*   } */
/*   printf("\n\n"); */
/*   for (int j = 0; j < 16 && i + j < len; j++) { */
/*     unsigned char c = data[i + j]; */
/*     printf("%c", (c >= 32 && c <= 126) ? c : '.'); */
/*   } */
/*   printf("\n"); */
/* } */


void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
  printf("\nPacket captured - length: %d bytes\n\n", header->len);
  print_hex_ascii(packet, header->caplen);
}

void capture_live(const char *dev_name) {
  char errbuff[PCAP_ERRBUF_SIZE];
  pcap_t *handle;

  handle = pcap_open_live(dev_name, SNAP_LEN, PROMISC, TIMEOUT_MS, errbuff);
  if (handle == NULL) {
    fprintf(stderr, "ERROR: Could not open the device %s. \n %s", dev_name, errbuff);
    exit(1);
  }
  printf("Listening on device: %s\n", dev_name);
  pcap_loop(handle, 0, packet_handler, NULL);
  pcap_close(handle);
}
