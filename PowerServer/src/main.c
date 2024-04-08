#include <stdio.h>
#include "../include/server.h"

int main()
{
    printf("Starting the Server\n");
    server_t* server = Server__create("127.0.0.1", 8080);
    Server__start(server);
    printf("Exiting the Server\n");
    Server__destroy(server);
    printf("Cleaned up the Server\n");
}