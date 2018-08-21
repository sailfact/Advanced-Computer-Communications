#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <signal.h>

#define	MAXLINE	4096
#define	BUFFSIZE	8192
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52001
#define	SERV_SCTP_PORT	52001
#define SERV_MAX_SCTP_STRM	10
#define	SA	struct sockaddr
#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))
