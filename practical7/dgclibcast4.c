#include	"acc.h"

static void	recvfrom_alarm(int);

void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int				n;
	const int		on = 1;
	char			sendline[MAXLINE], recvline[MAXLINE + 1];
	fd_set			rset;
	sigset_t		sigset_alrm, sigset_empty;
	socklen_t		len;
	struct sockaddr	*preply_addr;
 
	preply_addr = (struct sockaddr *) Malloc(servlen);

	Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

	FD_ZERO(&rset);

	sigemptyset(&sigset_empty);
	sigemptyset(&sigset_alrm);
	sigaddset(&sigset_alrm, SIGALRM);

	Signal(SIGALRM, recvfrom_alarm);

	while ((int *) Fgets(sendline, MAXLINE, fp) != NULL) {
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		sigprocmask(SIG_BLOCK, &sigset_alrm, NULL);
		alarm(1);
		for ( ; ; ) {
			FD_SET(sockfd, &rset);
			n = pselect(sockfd+1, &rset, NULL, NULL, NULL, &sigset_empty);
			if (n < 0) {
				if (errno == EINTR)
					break;
				else
					err_sys("pselect error");
			} else if (n != 1)
				err_sys("pselect error: returned %d", n);

			len = servlen;
			n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
			recvline[n] = 0;	/* null terminate */
		        //sleep(1); //still stuck in the infinite loop
			printf("from %s: %s",
					Sock_ntop_host(preply_addr, servlen), recvline);
		}
	}
}

static void
recvfrom_alarm(int signo)
{
	return;		/* just interrupt the recvfrom() */
}
