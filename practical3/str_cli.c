#include	"acc.h"

void str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE];
	struct message *msg = (struct message *)Malloc(sizeof(struct message));
	// bzero(&msg, sizeof(struct message));

	while ((void *) Fgets(sendline, MAXLINE, fp) != NULL) {
		write(sockfd, sendline, strlen(sendline));
		
		printf("receiving\n");
		if (read(sockfd, (struct message)msg, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		write(stdout, msg->msg, msg->length);
	}
}
