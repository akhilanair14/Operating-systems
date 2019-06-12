
#ifndef PROD_CON_H
#define PROD_CON_H 
//--------------Headers---------------
#include <time.h>   
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

//------------contant declaration------------------
extern int size;

//--------------structure declarations------------
typedef struct 
{
int putindex; //head of circular buffer
int getindex; //tail of circular buffer
int Buffer[]; //buffer to store variable
}buffer;
buffer bfr;  //declare buffer variable

typedef struct
{
int bfrsize;
int current;
int num_producer;
int num_consumer;
}args; 

//--------------declare mutex----------
extern pthread_mutex_t mutex;

//------------declare semaphores----------
extern sem_t full, empty;

//------------function prototypes------------
extern void *producer(void* param);
extern void *consumer(void* param);

#endif

