#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
	int sockfd, n, addrlen;
	struct sockaddr_in servaddr, addr;
	char buff[1024];

	if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0){
		perror("socket"); exit(1);
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(4000);

	printf("Enter message : \n");
	while (1){
		//scanf("%[^\n]",buff);
		fgets(buff,sizeof(buff),stdin);
		if (sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
			perror("sendto");
		}
		addrlen = sizeof(addr);
		if (recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&addr,&addrlen) < 0){
			perror("recvfrom");
		}
		printf("%s\n",buff);
	}
	close(sockfd);
}

