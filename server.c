#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <signal.h>

#define MAXIMUM_CONNECTION 100

#define BUFFER_SIZE 1024

/* to run the code use ./server 127.0.0.1 5050 */


void signalHandler(int signal_num)
{

    printf("\nYou just pressed <control-C>, however you can't close server, try <control-Z> ");

    signal(SIGINT, SIG_IGN);

}

int main(int argc, char *argv[])
{



    if (argv[1] == NULL)
    {
        printf("\033[1;31m");
        printf("IP address is empty\n");
        exit(0);
    }

    if (argv[2] == NULL)
    {
        printf("\033[1;31m");
        printf("Port address is empty\n");
        exit(0);
    }

    const char *ipaddress = argv[1];

    const int port = atoi(argv[2]);

    // signalling to ignore control-C
    signal(SIGINT, signalHandler);

    

    int sockfd, clientSock, bytes, index = 0;

    struct sockaddr_in serverAddr, clientAddr;

    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;

    serverAddr.sin_port = htons(port);

    serverAddr.sin_addr.s_addr =inet_addr(ipaddress);

    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) >= 0)
    {
        printf("\033[0;32m");
        printf("\n successfully binded the address to socket");
    }

    listen(sockfd, MAXIMUM_CONNECTION);

    char buffer[BUFFER_SIZE], message[BUFFER_SIZE];

    while (1)
    {

        socklen_t clientAddrLen = sizeof(clientAddr);

        if (clientSock = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen))
        {
            printf("\033[0;32m");
            printf("\n client accepted");
        }

        memset(buffer, '\0', sizeof(buffer));
        memset(message, '\0', sizeof(message));

        bytes = recv(clientSock, buffer, BUFFER_SIZE - 1, 0);

        buffer[BUFFER_SIZE] = '\0';

        printf("\n Received data: ");

        fputs(buffer, stdout);

        printf("\n Type data to send: ");

        while ((message[index++] = getchar()) != '\n')
            ;

        message[BUFFER_SIZE] = '\n';

        send(clientSock, message, sizeof(message), 0);
    }
    shutdown(sockfd, SHUT_RDWR);
    exit(1);
}