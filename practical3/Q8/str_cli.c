#include	"acc.h"

void str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE];
	struct message msg = NULL;
	bzero(&msg, sizeof(struct message));

	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL) {
		printf("1\n");
		write(sockfd, sendline, strlen(sendline));
		
		printf("receiving\n");
		if (read(sockfd, &msg, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		write(stdout, msg.msg, msg.length);
	}
}
