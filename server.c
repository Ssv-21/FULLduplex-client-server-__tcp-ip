#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>

void main(int argc,char *argv[]){

        int sockfd;
        struct sockaddr_in serverAddr;
        char g1[100],g2[100];
        int newSocket;
        struct sockaddr_in newAddr;

        socklen_t addr_size;
        char buffer[1024];

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("...Server Socket Created Sucessfully...\n");
        memset(&serverAddr, '\0', sizeof(serverAddr));

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(atoi(argv[1]));
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        printf("Binded to the Port number: %s.\n", argv[1]);

        listen(sockfd, 5);
        printf("...Listening...\n");

        newSocket = accept(sockfd, NULL, NULL);
        int g=fork();
        if(g==0)
        {
            while(1)
            {
               printf("enter message to client..:\n");
               scanf("%s",g1);
               send(newSocket, &g1, sizeof(g1), 0);
            }
        }
        else
        {
            while(1)
            {
              recv(newSocket,&g2,sizeof(g2),0);
             printf("client message is: %s \n",g2);
            }
        }
        
        printf("...Closing the connection...\n");


}

