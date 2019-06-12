/*--------------------------Header files----------------------*/
  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
  #include <unistd.h>
  #include <pthread.h>
  #include <semaphore.h>
  #include <time.h>
  #include "prod_con.h"
  #include "prod_con.c"
  
/*-----------------------Global variables--------------------*/
int size ;
extern time_t t;

/*-----------------------thread functions--------------------*/
void *producer(void* param);
void *consumer(void* param);


/*-----------------------------Main function-------------------*/
int main(int argc, char **argv){
   if (argc != 4)
   {
   printf("ERROR: Provide exactly three arguments.\n");
   exit(1);
   }
   args send;  //data type storing count of producer and consumer thread
   int i;		//initialization of counter index to create threads
   send.bfrsize = atoi (argv[1]);
   size  = send.bfrsize;
   send.num_producer = atoi (argv[2]);
   send.num_consumer = atoi (argv[3]);
   pthread_mutex_init(&mutex, NULL);
   sem_init(&empty, 0, send.bfrsize); // semaphore creation to check empty buffers and setting the intial value to buffer size
   sem_init(&full, 0, 0);		// semaphore creation to check full buffers and setting the intial value to buffer size
   // -----------------------------pthreads-------------------
   pthread_t producers[send.num_producer]; 
   pthread_t consumers[send.num_consumer];
   for(i = 0; i < send.num_producer; i++)
{  send.current=i;
   printf ("Main :started producer %d \n", i);
   pthread_create(&producers[i], NULL, producer, &send);// thread created based on number of producers user gave
   sleep(0.5);
   }
   
for(i = 0; i < send.num_consumer; i++)

{ send.current=i;
printf ("Main : started consumer %d \n", i);
if (pthread_create(&consumers[i], NULL, consumer, &send))// thread created based on number of consumer user gave
printf ("error");
sleep(0.5);

}

   for(i = 0; i < send.num_producer; i++)
   {pthread_join(producers[i], NULL);
    printf ("Main : Producer %d joined\n", i);
}
   for(i = 0; i < send.num_consumer; i++)
{   pthread_join(consumers[i], NULL);
    printf ("Main : Consumer %d joined\n", i);
}
   pthread_mutex_destroy(&mutex);
   sem_destroy(&full);
   sem_destroy(&empty);
   printf ("Main : Program is complete\n");
   return 0 ;

}



