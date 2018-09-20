#include	"acc.h"

void str_file(int sockfd)
{
	ssize_t		n, read;
	char		line[MAXLINE];
	char		buffer[MAXLINE];
	FILE 		*fp;
	long 		numbytes;

	while (1) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		fp = Fopen("test.txt", "r");

		if (fp != NULL) {
			fseek(fp, 0L, SEEK_END);
			numbytes = ftell(fp);
			fseek(fp, 0L, SEEK_SET);

			if (buffer != NULL) {
				fread(buffer, sizeof(char), numbytes, fp);
			}
		}

		Write(0, buffer, numbytes);
		Writen(sockfd, buffer, numbytes);
		
		fclose(fp);
	}
}
