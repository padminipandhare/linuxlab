//server programming
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//function declaration
void error(const char *msg);

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[255];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     //checking the port no is entered or not
     if (argc < 2) {
         fprintf(stderr,"Port no is not mentioned,Please mention it,& should be above 1024\n");
         exit(1);
     }

     //creating socket programming
     sockfd = socket(AF_INET, SOCK_STREAM, 0);//sock_stream is network type and default is 0.
     if (sockfd < 0)
        error("Error in opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     //making binding with network
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     //accept the connection from client
     newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
     if (newsockfd < 0)
          error("ERROR in accepting the connection from client");
     while(1)
     {
         //Reding message from client
         bzero(buffer,256);//clear buffer
         n = read(newsockfd,buffer,255);
         if (n < 0)
            error("ERROR  in reading message from socket");
         printf("Client: %s\n",buffer);

         //Write message to client
         bzero(buffer,256);//clear buffer
         fgets(buffer,255,stdin);
         n = write(newsockfd,buffer,strlen(buffer));
         if (n < 0)
            error("ERROR in writing message to socket");

         int i=strncmp("Bye" , buffer, 3);
         if(i == 0)
               break;
     }
     close(newsockfd);
     close(sockfd);
     return 0;
}

//function defination for error message
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
