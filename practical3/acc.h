#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <pthread.h>

#define	MAXLINE	4096
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52001
#define	SA	struct sockaddr

struct message {
    int type;
    char msg[MAXLINE];
    size_t length;
};
