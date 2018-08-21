#include	"acc.h"

#define	NLOOP 1000

int	counter;		/* this is incremented by the threads */
pthread_mutex_t	counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*doit(void *);

int
main(int argc, char **argv)
{
	pthread_t	tidA, tidB, tidC;

	pthread_create(&tidA, NULL, &doit, NULL);
	pthread_create(&tidB, NULL, &doit, NULL);
	pthread_create(&tidC, NULL, &doit, NULL);

		/* 4wait for both threads to terminate */
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);
	pthread_join(tidC, NULL);

	exit(0);
}

void *
doit(void *vptr)
{
	int		i, val, j;

	/*
	 * Each thread fetches, prints, and increments the counter NLOOP times.
	 * The value of the counter should increase monotonically.
	 */

	for (i = 0; i < NLOOP; i++) {
		pthread_mutex_lock(&counter_mutex);

		val = counter;
		printf("TID-%d: %d, loop-%d\n", pthread_self(), val + 1, i);
		counter = val + 1;

		for (j=0; j< 50000; j++) {
		}

		pthread_mutex_unlock(&counter_mutex);
	}

	return(NULL);
}
