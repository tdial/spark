#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(const char* msg) { fprintf(stderr, "error %d: %s\n", errno, msg); }

int main(int argc, char* argv[]) {
  // Create an unbound TCP socket.
  int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (listener < 0) {
    error("failed to create listener socket");
    return EXIT_FAILURE;
  }

  // We'll bind to any address on the local interface(s). To do this, we
  // first initialize an address structure to hold the "wildcard" address;
  // this means that when we eventually bind the socket, connections will
  // be accepted arriving on any of the existing interfaces. Note also
  // that we specify a port number of zero. This has a special meaning:
  // it tells the operating system to choose a port for us from the so-
  // called "ephemeral port range." To determine which port was assigned,
  // we must us the getsockname() function (see below.)
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(0);

  // Bind the socket using the address structure built above.
  int status = bind(listener, (const struct sockaddr*)&addr, sizeof(addr));
  if (status != 0) {
    close(listener);
    error("failed to bind listener socket");
    return EXIT_FAILURE;
  }

  // Since we asked to bind using an ephemeral port, we call getsockname() in
  // order to determine the port selected by the operating system.
  struct sockaddr_in bound_addr = {0};
  socklen_t len = sizeof(bound_addr);
  status = getsockname(listener, (sockaddr*)&bound_addr, &len);
  if (status != 0) {
    close(listener);
    return EXIT_FAILURE;
  }

  // Put socket into listening mode. We specify a "backlog" size of 5, which
  // means that up to five pending connections can pile up in the connection
  // queue before we accept() them. Any more than that will be rejected.
  status = listen(listener, 5);
  if (status != 0) {
    close(listener);
    error("failed to put socket into listening state");
    return EXIT_FAILURE;
  }

  // Print the port number that we're listening on.
  printf("listening on port %d\n", ntohs(bound_addr.sin_port));

  for (;;) {
    // Accept a new client connection. If we wanted to, we could pass an
    // address structure to learn the remote address of the client, but
    // for this example, we'll pass NULL to ignore it.
    int client = accept(listener, NULL, NULL);

    // The accept() function returns -1 on error. If this occurs, we print
    // an error and quit. Otherwise, 'client' will be populated with a
    // socket descriptor that we can use to communicate with the client.
    // In this demo, we'll just close the connection and report that we
    // handled a client.
    if (client < 0) {
      error("failed to accept connection");
      break;
    } else {
      close(client);
      printf("handled client connection\n");
    }
  }

  // Close the listener socket.
  close(listener);

  return 0;
}
