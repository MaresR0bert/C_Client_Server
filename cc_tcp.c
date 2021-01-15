#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
} 

int main(int argc, char *argv[])
{
    int sockfd, port, n; //declarare variabile
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256]; //creare buffer
    port = 8210; //asignare port
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //creare socket
    if (sockfd < 0) 
        error("ERROR opening socket"); //validare socket
    server = gethostbyname(""); //asignare host
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    } //validare host
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; //indicare retea
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(port); //indicare port
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting"); //validare conexiune
    printf("Type the number of the wanted command\nCommand List:\n1-Joke\n2-Current Time\n");
    printf("Enter command: "); //print pentru interfata
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer)); //scriere pe socket
    if (n < 0) 
         error("ERROR writing to socket"); //validare la scriere
    bzero(buffer,256);
    n = read(sockfd,buffer,255); //primire mesaj si adaugare in buffer
    if (n < 0) 
         error("ERROR reading from socket"); //validare la citire
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}
