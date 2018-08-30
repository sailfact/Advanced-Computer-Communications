/*********************************************************************
	Practical1
	daytimetcpsrv.c
	From Stevens' Textbook

*********************************************************************/
#include	"acc.h"


int
main(int argc, char **argv)
{
	int				listenfd, connfd;
	socklen_t		len;
	struct sockaddr_in	servaddr, cliaddr;
	char			buff[MAXLINE];
	time_t			ticks;
	const char		*ptr;

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
		fprintf(stderr, "socket creation failed\n");
		exit (1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_TCP_PORT); /* daytime server */

	printf("%s|%d",inet_ntop(AF_INET, &servaddr.sin_addr, buff, sizeof(buff)), servaddr.sin_port );

	if ( (bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0) {
		fprintf(stderr, "bind failed\n");
		exit (1);
	}


	if ( listen(listenfd, LISTENQ) < 0) {
		fprintf(stderr, "listen failed\n");
		exit (1);
	}

	for ( ; ; ) {
		len = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (SA *) &cliaddr, &len)) < 0 ) {
			fprintf(stderr, "accept failed\n");
			exit (1);
		}

		if (getpeername(listenfd, (SA *) &cliaddr, &len) < 0) {
			fprintf(stderr, "getpeername failed\n");
			exit (1);
		}

		if( (ptr = inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff))) == NULL) {
			fprintf(stderr, "inet_ntop error \n");
			exit (1);
		}
		printf("Server: connection from %s, port %d\n", ptr, ntohs(cliaddr.sin_port));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

		if ( send(connfd, buff, strlen(buff), 0) != strlen(buff)) {
			fprintf(stderr, "accept failed\n");
			exit (1);
		}

		if ( close(connfd) == -1) {
			fprintf(stderr, "accept failed\n");
			exit (1);
		}
	}
}
