#include	"acc.h"

void str_file(int sockfd)
{
	ssize_t		n;
	char		line[MAXLINE];
	char		buffer[MAXLINE];
	const char 	*filename;
	int 		inFile, n_char = 0;

	for ( ; ; ) {
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */
		printf("%s", line);
		bcopy(line, filename, sizeof(line));

		if ((inFile=open(line, O_RDONLY)) != -1) {
			while((n_char=Readline(inFile, buffer, MAXLINE)) != 0) {
				n_char=Writen(sockfd,buffer,n_char);
				// Writen(sockfd, buffer, n_char);
			}
			Close(inFile);
		}
		else
			return;
	}
}
