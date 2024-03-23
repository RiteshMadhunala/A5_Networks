#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/sem.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "msocket.h"
#define SOCK_MTP 3
// #ifdef DEBUG
// #defineprintf printf
// #else
// #defineprintf //
// #endif

int main()
{
    initialize_semaphores();

    int sockfd = m_socket(AF_INET, SOCK_MTP, 0);
    printf("%d\n", sockfd);
    if (sockfd < 0)
    {
        printf("Socket creation Failed\n");
        return 0;
    }

    char IP[20] = "127.0.0.1";
    int SPORT = 50006;

    char DIP[20] = "127.0.0.1";
    int DPORT = 60006;

    printf("socket created m_sockid:%d\n", sockfd);

    if (m_bind(sockfd, IP, SPORT, DIP, DPORT) < 0)
    {
        printf("Bind Failed\n");
        return 0;
    }
    printf("%d\n", sockfd);
    printf("Bind successful\n");
    //printf("using sendto now\n");

    while (1)
    {
        char buffer[1024];

        printf("Enter message(1 to QUIT)\n");

        scanf("%s", buffer);
        printf("%s\n", buffer);
        if (strcmp(buffer, "1") == 0)
            break;
       printf("using sendto now\n");
        int n = m_sendto(sockfd, buffer, strlen(buffer) + 1, IP, SPORT, DIP, DPORT);
        printf("n= %d\n", n);

        while (1)
        {
            // printf("inside while\n");
            int n = m_recvfrom(sockfd, buffer, 1000);
            if (n != -1)
            {
                printf("n %d\n", n);
                printf("Recieved:\n %s\n", buffer);
                if (strcmp(buffer, "0") == 0)
                    break;
                break;
            }
        }
    }
    sleep(2);
    m_close(sockfd);
    return 0;
}