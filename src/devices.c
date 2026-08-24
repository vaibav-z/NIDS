#include <stdio.h>
#include <pcap.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>


int devices(void) {
  pcap_if_t *alldevs;
  pcap_if_t *dev;
  char errbuf[PCAP_ERRBUF_SIZE];

  /* Find all available devices */
  if (pcap_findalldevs(&alldevs, errbuf) == -1) {
    fprintf(stderr, "Error finding devices: %s\n", errbuf);
    exit(1);
  }

  if (alldevs == NULL) {
    printf("No interfaces found. Try running as root/sudo.\n");
    exit(1);
  }

  /* Print the list */
  for (dev = alldevs; dev != NULL; dev = dev->next) {
    printf("%s \n", dev->name);

    /* Print flags */
    if (dev->flags & PCAP_IF_LOOPBACK)
      printf(" Loopback interface\n");
    if (dev->flags & PCAP_IF_UP)
      printf(" Up\n");
    if (dev->flags & PCAP_IF_RUNNING)
      printf(" Running\n");

    /* Print addresses */
    for (pcap_addr_t *a = dev->addresses; a != NULL; a = a->next) {
      if (a->addr && a->addr->sa_family == AF_INET) {
	struct sockaddr_in *sa = (struct sockaddr_in *)a->addr;
	printf(" IPv4: %s\n", inet_ntoa(sa->sin_addr));
      }
    }
  }
}
