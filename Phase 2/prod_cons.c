/---------------Headers---------------

#include "prod_con.h"

//------------define variables------------
time_t t=0;
buffer Bfr = {0,0,{0}};
pthread_mutex_t mutex;
sem_t full, empty;

//---------------declare threads-------------
void *producer(void* param);
void *consumer(void* param);


//---------------producer()----------------------
void *producer(void* param)
{

//wait on empty place on buffer to place an item
sem_wait(&empty);
 //wait for the critical area access
pthread_mutex_lock(&mutex);

 args* data = (args*)param;
 int Current = data->current;
 int producers = data->num_producer;
 int Bfrsize =  data->bfrsize;
 printf("P:%d Producing %d values\n",Current, 2*Bfrsize);
        //check if queue is full
 int i = 0;
  while (i< 2*Bfrsize) //each producer put 2*buffersize data into queue
{ 
    if(!(((Bfr.putindex + 1) % Bfrsize ) == Bfr.getindex)) //if queue is not full
          { 
            srand((unsigned)time (&t));
            //Place the item on buffer
            Bfr.Buffer[Bfr.putindex] = rand()%11;
            printf("P:%d Writing %d to position %d\n",Current,Bfr.Buffer[Bfr.putindex],Bfr.putindex);
            //Increment the 'head' index
            Bfr.putindex = (Bfr.putindex + 1) % Bfrsize;
            i++;
            if (i==2*Bfrsize)
            printf("P:%d Exiting \n",Current);//exit when done with writing 2*buffersize data
           }

        else  //if buffer is full
    {
      printf("P:%d Blocked due to full buffer\n",Current);
      }
//release the critical area access
pthread_mutex_unlock(&mutex);
 //Post the full place
sem_post(&full);
sleep(1);
}

}

//-------------------Consumer()--------------------------
void *consumer(void* param)
{
//wait on filled place on buffer to consume an item
sem_wait(&full);
//wait for the critical area access
pthread_mutex_lock(&mutex);
//convert void array to structure
args* data1 = (args*)param;
int Bfrsize1 = data1->bfrsize;
int Current1 = data1->current;
int consumers1 = data1->num_consumer;
int producers1 = data1->num_producer;
//Print Consuming Values
printf("C:%d Consuming %d values\n",Current1, consumers1);
int j=0;
while (j < ((2*Bfrsize1*producers1)/consumers1)) //even distribution of data read by consumer
{
if(!(Bfr.putindex == Bfr.getindex))
{           printf("C:%d Reading %d from position %d \n",Current1,Bfr.Buffer[Bfr.getindex],Bfr.getindex);
            //Consume an item on buffer
            Bfr.Buffer[Bfr.getindex] = 0;
            //Increment the 'out' index
            Bfr.getindex = (Bfr.getindex + 1) % Bfrsize1 ;
            j++;
            if (j == (2*Bfrsize1*producers1))//exit when done with reading
            printf("C:%d Exiting \n",Current1);

}
else
{
 printf("C:%d Blocked due to empty buffer\n",Current1);

}
//release the critical area access
pthread_mutex_unlock(&mutex);
 //Post the empty place
sem_post(&empty);
sleep(1);
}

}

