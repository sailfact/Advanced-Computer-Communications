#include	"acc.h"

void str_file(int sockfd)
{
	ssize_t		n, read;
	char		line[MAXLINE];
	char		buffer[MAXLINE];
	FILE 		*fp;

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		fp = fopen("test.txt", "r");

		if (fp != NULL) {
			n = fread(buffer, MAXLINE, 1, fp);
		}

		printf("%s", buffer);
		Writen(sockfd, buffer, strlen(buffer));
		
		fclose(fp);
	}
}
