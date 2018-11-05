#include	"acc.h"

void
str_echo(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];
	char 		sendline[MAXLINE] = {0};
	struct msghdr msg;
	for ( ; ; ) {
		if ( (n = recvmsg(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		printf("sending\n");
		while (sendmsg(sockfd, &msg, sizeof(msg));
	}
}
