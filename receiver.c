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
	int sockfd, n,addrlen;
	char buff[50];
	struct sockaddr_in addr;
	struct ip_mreq mreq;
	u_int yes = 1;

	if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0){
		perror("socket error");
		exit(0);
	}

	if (setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0){
		perror("sockopt");
		exit(0);
	}

	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(GROUPPORT);

	if (bind(sockfd,(struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("bind fail");
		exit(0);
	}

	mreq.imr_multiaddr.s_addr = inet_addr(GROUPADDR);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	printf("ad : %s\n",inet_ntoa(mreq.imr_interface));
	if (setsockopt(sockfd,IPPROTO_IP, IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0){
		perror("setsockopt");
		exit(0);
	}

	printf("Receiving Datagrams : \n");
	while (1){
		addrlen = sizeof(addr);
		if ((n = recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&addr, &addrlen)) < 0){
			perror("recvfrom");
		}
		//puts(buff);
		printf("%s\n",buff);
	}
	//close(sockfd);
}
