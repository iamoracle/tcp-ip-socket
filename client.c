#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

/* to run the code use ./client 127.0.0.1 5050 */

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("\033[1;31m");
        printf("Expecting 2 arguments %d given", argc - 1);
        exit(0);
    }

    char *inputServer = argv[1];

    int port = atoi(argv[2]), index = 0, activityCount = 0;

    char buffer[BUFFER_SIZE], message[BUFFER_SIZE];

    struct sockaddr_in serverAddr;

    int sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP), bytes;

    if (sockfd >= 0)
    {
        printf("\033[0;32m");
        printf("\n[%d] socket successfully initialized\n", activityCount++);
    }
    else
    {
        printf("\033[1;31m");
        printf("\nFailed to initialized socket, client exiting\n");
        exit(-1);
    }

    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_addr.s_addr = inet_addr(inputServer);

    serverAddr.sin_port = htons(port);

    serverAddr.sin_family = AF_INET;

    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) >= 0)
    {
        printf("\033[0;32m");
        printf("\n[%d] client successfully connected to %s on port %d\n", activityCount++, inputServer, port);
    }
    else
    {
        printf("\033[0;31m");
        printf("\nFailed to connecting to server, client exiting now\n");
        exit(-1);
    }

    while (1)
    {

        memset(buffer, '\0', sizeof(buffer));
        memset(message, '\0', sizeof(buffer));

        printf("Type your message here & press enter key: ");

        while ((message[index++] = getchar()) != '\n');

        message[BUFFER_SIZE] = '\0';

        if (send(sockfd, message, sizeof(message), 0) > 0)
        {
            printf("\033[0;32m");
            printf("\n[%d] client sent message to server\n", activityCount++);
            printf("\nMessage Sent: (%s)\n", message);
        }
        else
        {
            printf("\033[1;31m");
            printf("\nFailed to sending to server, client exiting\n");
            exit(-1);
        }

        bytes = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);

        buffer[BUFFER_SIZE] = '\0';

        if (bytes > 0)
        {
            printf("\033[0;32m");

            printf("\n[%d] client received message from server\n", activityCount++);
            printf("\nMessage Received: (%s)\n", buffer);
        }
        else
        {
            printf("\033[0;31m");
            printf("\nFailed to receive from server, client exiting\n");
        }
    }

    shutdown(sockfd, SHUT_RDWR);
    exit(1);
}
