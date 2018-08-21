#include	"acc.h"

void str_cli(FILE *od, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];
	FILE 	*fp;
	int 	rc;

	while ((void *) Fgets(sendline, MAXLINE, od) != NULL) {	// user input
		Writen(sockfd, sendline, strlen(sendline));	// write input to socket
		if ((fp = fopen(sendline, "w")) != NULL) {	// open file
			while ((rc = Readline(sockfd, recvline, MAXLINE))== 0) { // read from socket
				if (rc < 0) {
					err_quit("str_cli: server terminated prematurely");
				}
				if (fp!=NULL) {
					fprintf(fp,recvline); // write line to file
				}
			}
			fclose (fp);
		}
	}
}
