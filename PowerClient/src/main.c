#include <stdio.h>
#include <stdlib.h>
#include "../include/client.h"
#include "include/Handshake.h"

int main()
{
    printf("Starting Client\n");
    client_t* client = Client__create("127.0.0.1", 8080);
    Client__start(client);
    printf("Exiting Client\n");
    Client__destroy(client);
}