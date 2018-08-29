#include	"acc.h"

void str_file(int sockfd)
{
	ssize_t		n, read;
	char		line[MAXLINE];
	char		buffer[MAXLINE];
	int 		inFile;

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
		printf(">%s", line);
		
		inFile = Open("test.txt", O_RDONLY, S_IRUSR);
		if (inFile < 0)
			return;

		read = Readline(inFile, buffer, MAXLINE);
		Writen(0, buffer, MAXLINE);
		Writen(sockfd, buffer, MAXLINE);
		
		Close(inFile);
	}
}
