//-------AKHILA NAIR----------//
//-------PROJECT 3-----------//


//---------------------Sched_Sim.c-----------------------//
//-------------------------Headers----------------------//
#include <stdio.h>
#include "sched_sim.h"
//-------------------Global Variables----------------------//
int j,d,l;
q SJF_q,PRI_q,STCF_q,RR_q;
q FCFS_process_q, SJF_process_q,PRI_process_q,STCF_process_q,RR_process_q;
int print_seq (q Queue, int max_time, FILE *out);
int quantum =2;
int FCFS_CS,SJF_CS, PRI_CS, STCF_CS,  RR_CS;
float FCFS_WT,FCFS_TT,SJF_WT,SJF_TT,PRI_WT,PRI_TT,STCF_WT,STCF_TT,RR_WT,RR_TT;


//-----------------FCFS()-------------------------------//
void FCFS(process p[], int no_of_processes, int max_time, FILE *out, int interval)
{
int a=0,b=0,c=0,d=0,avg_tt=0, avg_wt=0;

for(a=0; a<=max_time; a+1)
{
while (b< no_of_processes)
{
if(p[b].arrival<=a)
{   p[b].start = a;
	while(c< ((p[b].timeburst)))
	{
		FCFS_process_q.buf[d] = p[b].pid;
	    d++;
		a++;
		c++;			}
	}	
	p[b].end = a;
	c=0;
	b++;
	}
	a--;
	
}


 fprintf(out,"\n*****FCFS Scheduling****");
 print_summary(FCFS_process_q, max_time, p ,no_of_processes, out, interval);
  fprintf(out,"\n******************************************************************\n");
	fprintf(out,"FCFS Summary (WT = wait time, TT = turnaround time):\n");
	fprintf(out,"\t PID \t WT \t TT\n");
	for(l=0;l<no_of_processes;l++)
	{
    p[l].turnaround = p[l].end - p[l].arrival;
    p[l].waiting = p[l].start-p[l].arrival;	
	fprintf(out,"\t %d \t %d \t %d\n", p[l].pid, p[l].waiting, p[l].turnaround);
    avg_wt +=p[l].waiting;	
    avg_tt +=p[l].turnaround;
        
    }
    FCFS_WT = (float)avg_wt/no_of_processes;
    FCFS_TT = (float)avg_tt/no_of_processes;
    fprintf(out,"\t AVG \t %.2f \t %.2f\n\n",((float)avg_wt/no_of_processes),((float)avg_tt/no_of_processes));
     FCFS_CS = print_seq (FCFS_process_q,max_time, out)	;
 }

 //---------------------------SJF()------------------------------------------//
void SJF(process process_list[], int no_of_processes, int max_time, FILE *out, int interval){
    int i = 0, avg_tt=0, avg_wt=0;
    int process_no = 0, start_time = 0, end_time = 0, wait_time = 0, turn_time = 0, curr_time = 0;
    int total_wait_time = 0, total_turn_time = 0;
    int processes_completed = 0;

    int process_status[no_of_processes];
    for(i=0;i<no_of_processes;i++){
        process_status[i] = 0;
    }

    curr_time = 0;
    while(processes_completed < no_of_processes){
        int min_val = 999999;
        int index = 0;
        for(i=0;i<no_of_processes;i++){
            if(process_status[i] == 0 && process_list[i].arrival <= curr_time && process_list[i].timeburst < min_val){
                min_val = process_list[i].timeburst;
                index = i;
            }
        }
        process_status[index] = 1;
        process_no = index + 1;
        if(processes_completed == 0)
            start_time = process_list[index].arrival;
        else
            start_time = curr_time;
        end_time = start_time + process_list[index].timeburst;
        process_list[index].waiting = start_time - process_list[index].arrival;
        process_list[index].turnaround = end_time - process_list[index].arrival;
         curr_time = curr_time + process_list[index].timeburst;
        SJF_q.buf[processes_completed] = process_list[index].pid;

        process_list[index].end = end_time ;
        process_list[index].start = start_time ;
        processes_completed++;
        
       }
    
    int k,l;
    for(j=0; j<max_time; )
    { for(i=0; i<no_of_processes;i++)
		{ int pro = SJF_q.buf[i];
		  for(k = process_list[pro].start ;k < process_list[pro].end ; k++)
		  {
			 SJF_process_q.buf[j] =  process_list[pro].pid;
		     j++; 			  
			  }	
			
			
				}
		}
		
	
    fprintf(out,"\n*****SJF Scheduling****");
    print_summary(SJF_process_q, max_time, process_list,no_of_processes, out, interval);
    
    fprintf(out,"\n******************************************************************\n");
	fprintf(out,"SJF Summary (WT = wait time, TT = turnaround time):\n");
	fprintf(out,"\t PID \t WT \t TT\n");
	for(l=0;l<no_of_processes;l++)
	{
	fprintf(out,"\t %d \t %d \t %d\n", process_list[l].pid, process_list[l].waiting, process_list[l].turnaround);
    avg_wt +=process_list[l].waiting;	
    avg_tt +=process_list[l].turnaround;
        
    }
    SJF_WT = (float)avg_wt/no_of_processes;
    SJF_TT = (float)avg_tt/no_of_processes;
    fprintf(out,"\t AVG \t %.2f \t %.2f\n\n",((float)avg_wt/no_of_processes),((float)avg_tt/no_of_processes));
    SJF_CS = print_seq (SJF_process_q,max_time, out)	;
    return;
}



//------------------------------Priority()---------------------------------------------------

void PRI(process process_list[], int no_of_processes, int max_time, FILE *out, int interval){
    int i = 0, avg_tt=0, avg_wt=0;
    int process_no = 0, start_time = 0, end_time = 0, wait_time = 0, turn_time = 0, curr_time = 0;
    int total_wait_time = 0, total_turn_time = 0;
    int processes_completed = 0;


    int process_status[no_of_processes];
    for(i=0;i<no_of_processes;i++){
        process_status[i] = 0;
    }

    curr_time = 0;
    while(processes_completed < no_of_processes){
        int min_priority = 999999;
        int index = 0;
        for(i=0;i<no_of_processes;i++){
            if(process_status[i] == 0 && process_list[i].arrival <= curr_time && process_list[i].priority < min_priority){
                min_priority = process_list[i].priority;
                index = i;
            }
        }
        process_status[index] = 1;
        process_no = index + 1;
        if(processes_completed == 0)
            start_time = process_list[index].arrival;
        else
            start_time = curr_time;
        end_time = start_time + process_list[index].timeburst;
        process_list[index].waiting = start_time - process_list[index].arrival;
        process_list[index].turnaround = end_time - process_list[index].arrival;
         curr_time = curr_time + process_list[index].timeburst;
        PRI_q.buf[processes_completed] = process_list[index].pid;

        process_list[index].end = end_time ;
        process_list[index].start = start_time ;
        processes_completed++;
        
       }
    
    int k,l;
    for(j=0; j<max_time; )
    { for(i=0; i<no_of_processes;i++)
		{ int pro = PRI_q.buf[i];
		  for(k = process_list[pro].start ;k < process_list[pro].end ; k++)
		  {
			 PRI_process_q.buf[j] =  process_list[pro].pid;
		     j++; 			  
			  }	
			
			
				}
		}
		
	
    fprintf(out,"\n*****Priority Scheduling****");
    fprintf(out,"\n******************************************************************\n");
	fprintf(out,"Priority Summary (WT = wait time, TT = turnaround time):\n");
	fprintf(out,"\t PID \t WT \t TT\n");
	for(l=0;l<no_of_processes;l++)
	{
	fprintf(out,"\t %d \t %d \t %d\n", process_list[l].pid, process_list[l].waiting, process_list[l].turnaround);
    avg_wt +=process_list[l].waiting;	
    avg_tt +=process_list[l].turnaround;
        
    }
    PRI_WT = (float)avg_wt/no_of_processes;
    PRI_TT = (float)avg_tt/no_of_processes;
    fprintf(out,"\t AVG \t %.2f \t %.2f\n\n",((float)avg_wt/no_of_processes),((float)avg_tt/no_of_processes));
    PRI_CS = print_seq (PRI_process_q,max_time, out)	;
    return;
}


//----------------------------------------STCF()--------------------------------------------//
void STCF (process process_list[], int no_of_processes, int max_time, FILE *out, int interval){

    int at[100],bt[100],rt[100],endTime,i,smallest,avg_tt=0, avg_wt=0;
    int remain=0,n,time,sum_wait=0,sum_turnaround=0;

    n = no_of_processes;
    for(i=0;i<n;i++){
        at[i] = process_list[i].arrival;
        bt[i] = process_list[i].timeburst;
        rt[i] = bt[i];
    }

    int start_time = 0, end_time = 0;
    rt[99] = 999999;

    int a[1000];
    for(i=0;i<1000;i++){
        a[i]=0;
    }

    int x = 0;
    for(time=0;remain!=n;time++){
        smallest=99;
        for(i=0;i<n;i++){
            if(at[i]<=time && rt[i]<rt[smallest] && rt[i]>0)
            {
                smallest=i;
            }
        }
        a[x] = smallest+1;
        STCF_q.buf[x] = a[x];
        x++;
        rt[smallest]--;
        if(rt[smallest]==0)
        {
            remain++;
            endTime=time+1;
            process_list[smallest].waiting = endTime-bt[smallest]-at[smallest];
            process_list[smallest].turnaround = endTime-at[smallest];
            sum_wait+=endTime-bt[smallest]-at[smallest];
            sum_turnaround+=endTime-at[smallest];
        }
    }
    i=0;
    start_time = 0;
    end_time = 0;

    time = 0;
    while(a[i]!=0){
        time++;
        if(a[i]!=a[i+1]){
            process_list[a[i-1]].start = start_time;
            process_list[a[i-1]].end  = time;
            start_time = time;
        }
        i++;
    }
   int j=0,k;
  for(j=0; j<max_time; )
    { for(i=0; i<no_of_processes;i++)
		{ int pro = STCF_q.buf[i];
		  for(k = process_list[pro].start ;k < process_list[pro].end ; k++)
		  {
			 STCF_process_q.buf[j] =  process_list[pro].pid;
		     j++; 			  
			  }	
						
				}
		}
		
 
    fprintf(out,"\n*****STCF Scheduling****");

    
    fprintf(out,"\n******************************************************************\n");
	fprintf(out,"STCF Summary (WT = wait time, TT = turnaround time):\n");
	fprintf(out,"\t PID \t WT \t TT\n");
	for(l=0;l<no_of_processes;l++)
	{
	fprintf(out,"\t %d \t %d \t %d\n", process_list[l].pid, process_list[l].waiting, process_list[l].turnaround);
    avg_wt +=process_list[l].waiting;	
    avg_tt +=process_list[l].turnaround;
        
    }
    STCF_WT = (float)avg_wt/no_of_processes;
    STCF_TT = (float)avg_tt/no_of_processes;
    fprintf(out,"\t AVG \t %.2f \t %.2f\n\n",((float)avg_wt/no_of_processes),((float)avg_tt/no_of_processes));
    STCF_CS = print_seq (STCF_process_q,max_time, out)	;


    return;
}



//-------------------------------------RR()----------------------------------------------
void RR(process p[], int no_of_processes, int max_time, FILE *out, int interval)
{

int a=0,b=0,c=0,avg_tt=0, avg_wt=0;
signed int d=0;


for(d=0;d<no_of_processes;d++)
{
	p[d].start = -1;
	p[d].remburst = p[d].timeburst;
	
	}
for(a=0; a<max_time; )
{
b=0;
while(b<no_of_processes)
{
if(p[b].arrival<=a)
{   if(p[b].start == -1)
	p[b].start = a;  
	for(c=0;c<quantum;c++)
	{   if(p[b].remburst !=0)
		{
		RR_process_q.buf[a] = p[b].pid;
		a++;
		p[b].remburst = p[b].remburst - 1;
	
	}
	    else
	    {p[b].end = a;
	     goto out1; }
	  
	}

		}
	
		
out1 : b++;
}

}	
 fprintf(out,"\n*****RR Scheduling****");
 fprintf(out,"\n******************************************************************\n");
	fprintf(out,"RR Summary (WT = wait time, TT = turnaround time):\n");
	fprintf(out,"\t PID \t WT \t TT\n");
	for(l=0;l<no_of_processes;l++)
	{
    p[l].turnaround = p[l].end - p[l].arrival;
    p[l].waiting = p[l].start-p[l].arrival;	
	fprintf(out,"\t %d \t %d \t %d\n", p[l].pid, p[l].waiting, p[l].turnaround);
    avg_wt +=p[l].waiting;	
    avg_tt +=p[l].turnaround;
        
    }
    RR_WT = (float)avg_wt/no_of_processes;
    RR_TT = (float)avg_tt/no_of_processes;
    fprintf(out,"\t AVG \t %.2f \t %.2f\n\n",((float)avg_wt/no_of_processes),((float)avg_tt/no_of_processes));
    RR_CS = print_seq (RR_process_q,max_time, out)	;
}






int running = 0,k=0;

//----------------------------Print summary()---------------------------------------------//
void print_summary(q reference_q, int max_time, process p[],int total_processes, FILE *out,int interval)
{  int c;
	for (c =0 ;c<=max_time; c++)
{   
	
	fprintf(out, "\n t= %d  ", c);
	int pro = reference_q.buf[k];
	fprintf(out,"\n CPU:");
	int pro1 = reference_q.buf[k - 1];
   	if (p[pro1].end == c)
	fprintf(out, " Finishing process %d ", pro1);
   
    
    if (p[pro].start < c && c< p[pro].end)
	{
	  fprintf(out, " Running process %d (remaining CPU burst = %d)", pro, p[pro].remburst); 
	   running = p[pro].pid;
	   p[pro].remburst = p[pro].remburst - interval;	
	} 
	
	if(p[pro].start == c)
	{   fprintf(out, " Loading process %d (CPU burst = %d)", pro, p[pro].timeburst);
		p[pro].remburst = p[pro].remburst - interval;	//Queue.running = p[pro].pid;
		}
	
	
	fprintf(out,"\n Ready Queue: ");
    for(d =1; d<=total_processes; d++)
	{
	if (p[d].arrival <= c && c< p[d].end )
	{	
	if(p[d].pid != running)
	fprintf(out,"- %d", p[d].pid);
	if(running == p[max_time].pid)
	fprintf(out,"empty");
	
}
}

	fprintf(out,"\n");
	k++;
    c= c+interval-1;	
    }
	
	k=0;
	
	}

//--------------------------Check context switch and sequence-----------------------------------//	
int print_seq (q Queue, int max_time, FILE *out)
{
int z=0, switch_count=0,i;	
int switch_buf [50];
	for (i=0; i<max_time; i++)
{
if(Queue.buf[i]!=Queue.buf[i+1])
{
  switch_count++;
  switch_buf[z] = Queue.buf[i];
  z++;
}
  
}
switch_count++;
switch_buf[z++] = Queue.buf[i-1];
fprintf(out,"\nProcess sequence: ");
for(z=0; z<switch_count; z++)
{
fprintf(out,"-%d", switch_buf[z]);	
	}
fprintf(out,"\n Context Switches: %d",switch_count);
return switch_count;
}



//--------------------------------Overall Summary--------------------------------------------//
void overall_summary(FILE *out)
{
fprintf(out,"\n**********OVERALL SUMMARY*************");
fprintf(out,"\n\nWait Time Comparision");
fprintf(out,"\n1 STCF        %.2f",STCF_WT);
fprintf(out,"\n2 SJF         %.2f",SJF_WT);
fprintf(out,"\n3 FCFS        %.2f",FCFS_WT);
fprintf(out,"\n4 RoundRobin  %.2f",RR_WT);
fprintf(out,"\n5 Priority    %.2f",PRI_WT);	
	
fprintf(out,"\n\nTURNAROUND Time Comparision");
fprintf(out,"\n1 STCF        %.2f",STCF_TT);
fprintf(out,"\n2 SJF         %.2f",SJF_TT);
fprintf(out,"\n3 FCFS        %.2f",FCFS_TT);
fprintf(out,"\n4 RoundRobin  %.2f",RR_TT);
fprintf(out,"\n5 Priority    %.2f",PRI_TT);

fprintf(out,"\n\nContext Switch Comparision");
fprintf(out,"\n1 STCF        %d",STCF_CS);
fprintf(out,"\n2 SJF         %d",SJF_CS);
fprintf(out,"\n3 FCFS        %d",FCFS_CS);
fprintf(out,"\n4 RoundRobin  %d",RR_CS);
fprintf(out,"\n5 Priority    %d",PRI_CS);	
	
	
	}
