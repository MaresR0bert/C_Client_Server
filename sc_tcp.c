#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
} 

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, port; //declarare variabile
     socklen_t clilen;
     char buffer[256]; //declarare buffer
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     time_t ticks; //declarare var de tip time 
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0); //creare socket
     if (sockfd < 0) 
        error("ERROR opening socket"); //validare socket
     bzero((char *) &serv_addr, sizeof(serv_addr));
     port = 8210; //asignare port
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY; //setare adresa host default
     serv_addr.sin_port = htons(port); //asignare port
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR on binding"); //validare la binding
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //accept
     if (newsockfd < 0) 
          error("ERROR on accept"); //validare la accept
     bzero(buffer,256);
     n = read(newsockfd,buffer,255); //citire buffer primit de la client
     if (n < 0) error("ERROR reading from socket"); //validare mesaj primit
     printf("Command: %s\n",buffer);
     int intBuf = atoi(buffer);
     if(intBuf == 1){
        n = write(newsockfd,"I invented a new word!\nPlagiarism\n",35); //trimitere catre client
     }else if(intBuf == 2){
        ticks = time(NULL);
        n = write(newsockfd,("%.24s\r\n",ctime(&ticks)),25); //trimitere catre client
     }else if(intBuf == 3){
        srand(time(NULL));
	int rando = rand();
        n = write(newsockfd,("Number: %s\r\n",(const void*)rando),11); //trimitere catre client
     }else{
        n = write(newsockfd,"Invalid command",15); //trimitere catre client
     } //executarea comenzi date de client
     if (n < 0) error("ERROR writing to socket"); //validare mesaj trimis
     close(newsockfd); 
     close(sockfd); //inchide socket
     return 0; 
}
