#include	"acc.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	printf("Enter File Name: ");
	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL) {
		printf("Sending request to server...\n");
		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Write(stdout, recvline, sizeof(recvline));
	}
}
