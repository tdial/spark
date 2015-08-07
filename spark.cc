#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(const char* msg) {
  fprintf(stderr, "error %d: %s\n", errno, msg);
}

int main(int argc, char* argv[])
{
  // Create a socket; this will be our listener.
  int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (listener < 0) {
    error("failed to create listener socket");
    return EXIT_FAILURE;
  }

  // Close the listenr socket.
  close(listener);

  return 0;
}
