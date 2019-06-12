
//-------AKHILA NAIR----------//
//-------PROJECT 3-----------//


 
//------------------------Headers-------------------------- //
#include<stdio.h>
#include<stdlib.h>
#include "sched_sim.h"
#include "sched_sim.c"

//-------------------Global variables-------------------//
	
int switch_count = 0;
int switch_buf [10];
int interval;



//----------------------Main()------------------------//
int main (int argc, char **argv[])
{
 if(argc !=4)                   //check arguments
 {
	printf("\n error in arguments");	 
	 
	 }
  FILE *in, *out;   //define files to be read and written to
  out = fopen (argv[2],"rb+");
  if (out == NULL)
  out = fopen (argv[2],"wb");  //open file
  int interval = atoi(argv[3]);
  int num, j;
  int i = 0;
  int k, l = 0;
  int buff[100];
  in = fopen(argv[1],"r");
  while (fscanf(in, "%d", &num)== 1)
 { buff[i] = num;       
   i++;
  }
  int total_processes = i/3;
  fclose(in);
  process p[total_processes];
  for ( j = 0 ; j<(i/3) ; j++)   //assign values to the process stucture
  {
  p[j].pid = j;
  p[j].timeburst = buff[k];
  p[j].remburst = p[j].timeburst;
  p[j].priority = buff[++k];
  p[j].arrival  = buff[++k];
  k++;
  }

int max_time = 0;
for (l=0 ;l<j ;l++)
{
max_time += p[l].timeburst; 
p[l].remburst = p[l].timeburst;	
	}

//---------------------Call Schedulers--------------------//
FCFS( p,total_processes, max_time, out, interval);
SJF( p,total_processes, max_time, out, interval);
PRI( p,total_processes, max_time, out, interval);
STCF( p,total_processes, max_time, out, interval);
 RR(  p,total_processes, max_time, out, interval);
 
//-----------------------Get Overall summary----------------//
overall_summary(out);
printf("DONE Scheduling !!");
close(out);  //close file
return 0;
}
