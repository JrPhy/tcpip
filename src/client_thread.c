// C program for the Client Side
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
// inet_addr
#include <arpa/inet.h>
#include <unistd.h>
 
// For threading, link with lpthread
#include <pthread.h>
int port;
char buf[4096], ip[16];
// Function to send data to
// server socket.
int timeout_recv(int fd, int *buf, int len, int nsec)
{
    struct timeval timeout;
    timeout.tv_sec = nsec;
    timeout.tv_usec = 0;

    printf("timeout_recv called, timeout %d seconds\n", nsec);

    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt error");
        exit(1);
    }

    int n = recv(fd, buf, len, 0);

    return n;
}

void* clienthread(void* args)
{
    int status = 0;
    char buf[4096];
    // Create a stream socket
    int client_request = *((int*)args);
    int network_socket;
    network_socket = socket(AF_INET,
                            SOCK_STREAM, 0);
 
    // Initialise port number and address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip);
    server_address.sin_port = htons(port);
 
    // Initiate a socket connection
    int connection_status = connect(network_socket,
                                    (struct sockaddr*)&server_address,
                                    sizeof(server_address));
    
    // Check for connection error
    if (connection_status < 0) {
        puts("Error\n");
        pthread_exit(NULL);
        return 0;
    }
 
    printf("Connection established\n");
 
    // Send data to the socket
    send(network_socket, &client_request,
         sizeof(client_request), 0);
    printf("Waiting for server\n");
    int nbytes, nread, kkk = 0;

    nread = timeout_recv(network_socket, &status, sizeof(status), 20);
    if (nread == 0) {
        printf("time out\n");
        shutdown(network_socket, SHUT_RDWR);
        return 0;
    }
    if(status == 1) printf("connect to server succesfully\n");
    else 
    {
        printf("server is full, exit!\n");
        exit(0);
    }
    time_t t;
    srand((unsigned) time(&t));
    int ggg = rand() % 500000;
    printf("ggg = %d\n", ggg);
    while (1) {
        kkk++; 
        if(kkk == 10000)
        {
            nbytes = send(network_socket, &ggg, sizeof(ggg), 0);
            if (nbytes < 0) {
                perror("send error");
                break;
            }
            else if (nbytes == 0) {
            
            }
        }
    }
    // Close the connection
    close(network_socket);
    pthread_exit(NULL);
    
    return 0;
}
 
// Driver Code
int main(int argc, char *argv[])
{
    // Initialize variables
    if (1 == argc) return 0;
    char buf[4096];
    char *ptr = strtok(argv[1], ":");
    if (ptr == NULL) return 0;
    strcpy(ip, ptr);
    ptr = strtok(NULL, ":");
    port = atoi(ptr);
    pthread_t tid;
    int client_request = 1;
 
    // Create thread
    pthread_create(&tid, NULL,
                    clienthread,
                    &client_request);
    //sleep(20);
    // Suspend execution of
    // calling thread
    pthread_join(tid, NULL);
}