//-------AKHILA NAIR----------//
//-------PROJECT 3-----------//


//--------------------Sched_Sim.h---------------------//


#ifndef SCHED_SIM_H
#define SCHED_SIM_H

//Declare Files
extern FILE *in, *out;

//-----------------process structure type-----------//
typedef struct 
{
int pid;
int timeburst;
int priority;
int arrival;
int start;
int end;
int finished;
int turnaround;
int waiting;
int remburst;
int begin;
}process;


//-----------------------q structure type---------------------
typedef struct
{ int head;
  int tail;
  int buf[250];
  int running;
		}q;

extern interval;

//---------------------------------Function Prototypes----------------------//
void FCFS(process p[], int no_of_processes, int max_time, FILE *out, int interval)	;	
void SJF(process process_list[], int no_of_processes, int max_time, FILE *out,int interval);
void PRI(process process_list[], int no_of_processes, int max_time, FILE *out, int interval);
void STCF (process process_list[], int no_of_processes, int max_time, FILE *out, int interval);
void RR(process process_list[], int no_of_processes, int max_time, FILE *out, int interval);
void print_summary(q reference_q, int max_time, process p[],int total_processes, FILE *out, int interval);
void overall_summary(FILE *out);



#endif
