#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

#define PORT 10000
#define ADDR 172.20.13.1

bool no_waitC(char llista){
	int taula;
	fd_set rfds;
	int sockett, nousocketfd;
	char l1, l2;
	char msg[256];
	char msg2[256];
	int estat;
	struct timeval to;

	taula = select(llista, &rfds, NULL, NULL, &to);
	if (taula[0] == llista[0]){ // Han de ser structs i no ints, pero select necessita que taula sigui int
		bzero(msg, 256);
		fgets(msg,256-1,stdin);
		write(sockett, msg, strlen(msg));
		return true;
	}
	else (taula[0]==llista[1]){ // Han de ser structs i no ints, pero select necessita que taula sigui int
		bzero(msg2,256);
		estat=read(nousocketfd,msg2,256-1);
		if(!estat){
			printf("Server disconnected\n");
			close(nousocketfd);
			close(sockett);
			return false;
		}
		else
			printf("Server says: %s",msg2);
	}
}

int main(void){
	int sockett;
	char missatge[256];
	struct hostent *server;
	struct sockaddr_in serverAddr;
	int s_msg;

	sockett=socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    while (1){
    	if(!no_waitC(missatge))
    		break;
    }

}