/*************************************************************************
 From "Practical Unix Programming", by Kay A. Robbins and Steven Robbins.

 This program simulates producer-consumer bounded queue problem. The producer thread writes the squares of integers from 1 to 100, while the consumers thread removes the values and sum them.
However, the producer and consumer threads are not synchronized, and thus, the final result is incorrect.
 
*************************************************************************/
#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define SUMSIZE 100
#define BUFSIZE 8

int sum = 0;

static int buffer[BUFSIZE];
static int bufin = 0;
static int bufout = 0;
static pthread_mutex_t  buffer_lock = PTHREAD_MUTEX_INITIALIZER;

/* Get the next item from buffer and put it in *itemp. */
void get_item(int *itemp)
{
   pthread_mutex_lock(&buffer_lock);
   *itemp = buffer[bufout];
   bufout = (bufout + 1) % BUFSIZE;
   pthread_mutex_unlock(&buffer_lock);
   return;
}

/* Put item into  buffer at position bufin and update bufin. */
void put_item(int item)
{
   pthread_mutex_lock(&buffer_lock);
   buffer[bufin] = item;
   bufin = (bufin + 1) % BUFSIZE;
   pthread_mutex_unlock(&buffer_lock);
   return;
}

void *producer(void * arg1)
{
   int i;
   for (i = 1; i <= SUMSIZE; i++)
      put_item(i*i);
   return NULL;    
}

void *consumer(void *arg2)
{
   int  i, myitem;
   for (i = 1; i <= SUMSIZE; i++) {
      get_item(&myitem);
      sum += myitem;
   }
   return NULL;
}
 
int main(void)
{
   pthread_t prodtid;
   pthread_t constid;
   int i, total;
                                                  /* check value */
   total = 0;
   for (i = 1; i <= SUMSIZE; i++)
      total += i*i;
   printf("The actual sum should be %d\n", total);
 
                                              /*  create threads */
   if (pthread_create(&constid, NULL, consumer, NULL))
      fprintf(stderr,"Could not create consumer");
   else if (pthread_create(&prodtid, NULL, producer, NULL))
      fprintf(stderr,"Could not create producer");
 
                               /* wait for the threads to finish */
   pthread_join(prodtid, NULL);
   pthread_join(constid, NULL);
   printf("The threads produced the sum %d\n", sum);
   exit(0);
}
