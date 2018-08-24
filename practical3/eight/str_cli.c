#include	"acc.h"

void str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];
	FILE *newFile;

	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL) {
		newFile = fopen(sendline, "w");

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");


	}
}
