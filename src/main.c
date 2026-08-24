#include "../include/devices.h"
#include "../include/dump.h"

#include <stdio.h>
#include <string.h>

void useage(void);

int main(int argc, char **argv) {
  if (argc < 2) {
    useage();
    return 0;
  }
  if (!strcmp(argv[1], "-list-devices")){
    devices();
  } else if (!strcmp(argv[1], "-hex-dump")){
    if (argc < 3) {
      printf("ERROR: Provide an interface to listen through (Make sure to use sudo) \n");
      return 1;
    }
    capture_live(argv[2]);
    
  } else {
    useage();
  }
  return 0;
}

void useage(void) {
  printf("USEAGE: COMMAND <SUBCOMMAND> <ARGS>\n"
	 "\n"
	 "<SUBCOMMANDS>:\n"
	 "   -list-devices: List all the available devices in this system\n"
	 "   -hex-dump <ARGS: LISTENING INTERFACE: listens and dumps all the hex data from that interface>\n");  
}
