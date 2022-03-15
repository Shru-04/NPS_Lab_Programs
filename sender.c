#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define GROUPADDR "225.0.0.70"
#define GROUPPORT 10000

int main(){
	int sockfd, n;
	char buff[50];
	struct sockaddr_in addr;

	if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0){
		perror("socket error");
		exit(0);
	}
	
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(GROUPADDR);
	addr.sin_port = htons(GROUPPORT);

	printf("Enter Messages :-\n");

	while (1){
		scanf("%s",buff);
		if (sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&addr,sizeof(addr)) < 0){
			perror("sendto");
			exit(0);
		}
		sleep(1);
	}
	//sleep(1);
}
