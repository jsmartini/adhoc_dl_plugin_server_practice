#include "echo_s2c_module.h"
#include "rb_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct
{
    int port;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int client_socket_fd;
    int server_socket_fd;

} echoServerContext_t;

// Internal Server Context Management API
int Echo_Server_Basic_Update(serverContext_t* serverContextPtr, void*)
{
    echoServerContext_t* server_ptr = (echoServerContext_t*)(serverContextPtr->instance_ptr);

    fd_set read_fds;
    int max_fd = server_ptr->server_socket_fd;
    FD_ZERO(&read_fds);
    FD_SET(server_ptr->server_socket_fd, &read_fds);

    select(max_fd + 1, &read_fds, NULL, NULL, NULL);

    if(FD_ISSET(server_ptr->server_socket_fd, &read_fds))
    {
        server_ptr->client_socket_fd = accept(server_ptr->server_socket_fd, (struct sockaddr*)NULL, NULL);
        //printf("Got clients on %s@%d\n", inet_ntoa())
        char buff[100] = {};
        int sz = recv(server_ptr->client_socket_fd, &buff[0], 100, 0);
        if (sz < 0) return;
        printf("Got %d bytes\n", sz);
        send(server_ptr->client_socket_fd, buff, sz, 0);
    }
};

serverContext_t* Echo_Init_Server_Context(void*)
{
    serverContext_t* new_server_instance = (serverContext_t*)malloc(sizeof(serverContext_t));
    new_server_instance->basic_interface = &echo_server_basic_interface;
    new_server_instance->instance_ptr = (void*)malloc(sizeof(echoServerContext_t));

    echoServerContext_t* server_ptr = (echoServerContext_t*)(new_server_instance->instance_ptr);
    memset(server_ptr, 0, sizeof(echoServerContext_t));

    server_ptr->port = 7777;
    server_ptr->server.sin_family = AF_INET;
    server_ptr->server.sin_port = htons(server_ptr->port);
    server_ptr->server.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt_val = 1;
    setsockopt(server_ptr->server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val));
    bind(server_ptr->server_socket_fd, (struct sockaddr*)&server_ptr->server, sizeof(server_ptr->server));
    listen(server_ptr->server_socket_fd, 10);

    printf("Initialized Echo Server\n");

    return new_server_instance;
};

int Echo_Destroy_Server_Context(serverContext_t* serverContextPtr, void*)
{
    close(((echoServerContext_t*)serverContextPtr->instance_ptr)->server_socket_fd);
    free(serverContextPtr->instance_ptr);
};

// Server Module Bootstrap Interface Specification
serverInterfaceBasic_t echo_server_basic_interface = 
{
    .Basic_Update = &Echo_Server_Basic_Update,
    .Init_Server_Context = &Echo_Init_Server_Context,
    .Destroy_Server_Context = &Echo_Destroy_Server_Context,
};
