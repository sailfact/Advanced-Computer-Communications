#include	"acc.h"

void str_file(int sockfd)
{
	ssize_t		n, read;
	char		line[MAXLINE];
	char		buffer[MAXLINE];
	FILE  		*fp;

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
		printf(">%s", line);
		
		fp = fopen("test.txt", "r");
		if (fp == NULL)
			return;

		while ((read = getline(buffer, MAXLINE, fp)) != -1) {
			printf("%s", buffer);
			Writen(sockfd, buffer, MAXLINE);
		}
		Fclose(fp);
	}
}
