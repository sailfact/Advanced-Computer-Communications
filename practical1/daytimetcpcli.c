/***********************************************************************
	Practical1
	daytimetcpcli.c
	from Stevens's Textbook

************************************************************************/
#include	"acc.h"

int
main(int argc, char **argv)
{
	int	sockfd, n;
	char	recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("socket error");
		return 1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	if (argc == 3)
		servaddr.sin_port   = htons(atoi(argv[2]));	
	else
		servaddr.sin_port = htons(SERV_TCP_PORT);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
		printf("inet_pton error for %s", argv[1]);
		return 1;
	}

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
		printf("connect error");
		return 1; 
	}

	printf("Client: ");
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF) {
			printf("fputs error");
			return 1;
		}
	}
	if (n < 0) {
		printf("read error");
		return 1;
	}

	exit(0);
}
