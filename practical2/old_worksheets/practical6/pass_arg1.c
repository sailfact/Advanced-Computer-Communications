/* BeginSourceFile args.c */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include	"acc.h"

void *thread_function(void *);
pthread_t create_thread();
int
main(int argc, char **argv)
{
	pthread_t threadID;

	threadID = create_thread();
	printf("Hello from your creator! My ID is %d \n", pthread_self());
	printf("I have just created a thread with ID %d \n", threadID);
	pthread_join(threadID, NULL);
	exit(0);

}

pthread_t 
create_thread()
{
	pthread_t threadID;
	int ap;
	int error;

	ap = pthread_self();
	error = pthread_create(&threadID, NULL, thread_function, (void *) &ap);
	if (error != 0)
	{
		printf("pthread_create failed due to %d\n", error);
		exit (1);
	}
	//sleep(2);  //Line A
	return(threadID);
	
}
void *
thread_function(void *arg)
{
	//sleep(2);  Line B

	int *argp = (void *) arg;

	printf("My creator ID is %d \n", *argp);
	printf("My thread ID: %d \n", pthread_self());
	return (NULL);
}
/* EndSourceFile */

