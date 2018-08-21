#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>
#include <signal.h>


#define	HAVE_MSGHDR_MSG_CONTROL	1
#ifdef	HAVE_PTHREAD_H
#include	<pthread.h>
#endif
typedef	void Sigfunc (int);

#define min(a,b)	((a) < (b) ? (a) : (b))
#define max(a,b)	((a) > (b) ? (a) : (b))
#define	MAXLINE	4096
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52001
#define	OK	52001
#define	SA	struct sockaddr
/* Our own header for the programs that use threads.
   Include this file, instead of "unp.h". */


#ifndef		__unp_pthread_h
#define		__unp_pthread_h


void	Pthread_create(pthread_t *, const pthread_attr_t *, void * (*)(void *), void *);
   /*void * (*)(void *), void *);*/
void	Pthread_join(pthread_t, void **);
void	Pthread_detach(pthread_t);
void	Pthread_kill(pthread_t, int);

void	Pthread_mutexattr_init(pthread_mutexattr_t *);
void	Pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
void	Pthread_mutex_init(pthread_mutex_t *, pthread_mutexattr_t *);
void	Pthread_mutex_lock(pthread_mutex_t *);
void	Pthread_mutex_unlock(pthread_mutex_t *);

void	Pthread_cond_broadcast(pthread_cond_t *);
void	Pthread_cond_signal(pthread_cond_t *);
void	Pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);
void	Pthread_cond_timedwait(pthread_cond_t *, pthread_mutex_t *,
							   const struct timespec *);

void	Pthread_key_create(pthread_key_t *, void (*)(void *));
void	Pthread_setspecific(pthread_key_t, const void *);
void	Pthread_once(pthread_once_t *, void (*)(void));

#endif	/* __unp_pthread_h */
