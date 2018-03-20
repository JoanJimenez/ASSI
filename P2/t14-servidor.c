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

bool no_waitS(char llista){
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
			printf("Client disconnected\n");
			close(nousocketfd);
			close(sockett);
			return false;
		}
		else
			printf("Client says: %s",msg2);
	}
}

int main(void){
	int sockett, nousocketfd;
	char missatge[256];
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;
	int msg;


	sockett=socket(AF_INET, SOCK_STREAM, 0);
	if (sockett < 0)
		perror("Error al obrir socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (bind(sockett, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("Error al fer binding");
    listen(sockett,1);
    clilen = sizeof(cli_addr);
    nousocketfd = accept(sockett,
    	(struct sockaddr *) &cli_addr,
    	&clilen);
    if (nousocketfd < 0)
    	error("Error a l'accept");
    bzero(missatge, 256);
		fgets(missatge,256-1,stdin);
    while(1){
    	if (!no_waitS(missatge))
    		break;
    }
}