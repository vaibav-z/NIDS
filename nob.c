#define NOB_IMPLEMENTATION
#include "include/nob.h"

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-o", "bin/main", "src/devices.c", "src/dump.c", "src/main.c", "-lpcap");
  if (!nob_cmd_run(&cmd)) return 1;
  return 0;
}
 
