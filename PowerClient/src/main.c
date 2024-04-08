#include <stdio.h>
#include "../include/client.h"

int main()
{
    printf("Starting the Client\n");
    client_t* client = Client__create("127.0.0.1", 8080);
    Client__start(client);
    printf("Exiting the Client\n");
    Client__destroy(client);
    printf("Cleaned up the Client\n");
}