#include	"acc.h"

void
str_echo(int sockfd, int timeout)
{
	ssize_t			n;
	char			line[MAXLINE];
	struct timeval 	timeval;
	fd_set		rset;
	timeval.tv_sec = timeout;
	timeval.tv_usec = 0;
	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
	for ( ; ; ) {
		if (Select(sockfd+1, &rset, NULL, NULL, &timeval) <= 0)
		{
			snprintf(line, sizeof(line), "input error\n");
			n = strlen(line);
			Writen(sockfd, "\nTimes up\n", n);
			return;
		}
		else 
		{
			if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
				return;		/* connection closed by other end */
			Writen(sockfd, line, n);

		}
	}
}
