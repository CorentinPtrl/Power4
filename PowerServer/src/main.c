#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "../include/server.h"

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    exit(0);
}

int main()
{
    signal(SIGINT, intHandler);
    printf("Starting the Server\n");
    server_t* server = Server__create("127.0.0.1", 8080);
    Server__start(server);
    printf("Exiting the Server\n");
    Server__destroy(server);
    printf("Cleaned up the Server\n");
}