#include<stdio.h>
#include<conio.h>

struct process {
		int process;
		int P ;
		int AT ;
		int BT ;
		int RT ;
		int processed ;
};

struct process queue1[50], queue2[50], queue3[50] ;

int rear1 = -1 ;
int front1 = -1 ;
int rear2 = -1 ;
int front2 = -1 ;
int rear3 = -1 ;
int front3 = -1 ;


void queue1Push(struct process proc1) {
	if(front1 == -1) {
		front1 = 0 ;
	}
	rear1 = rear1 + 1 ;
	queue1[rear1] = proc1 ;
}


void queue1Pop() {
	front1 = front1 + 1 ;
}


struct process queue1Front() {
	return queue1[front1] ;
}


void queue2Push(struct process proc1) {
	if(front2 == -1) {
		front2 = 0 ;
	}
	rear2 = rear2 + 1 ;
	queue2[rear2] = proc1;
}


void queue2Pop() {
	front2 = front2 + 1 ;
}


struct process queue2Front() {
	return queue2[front2] ;
}


void queue3Push(struct process proc1) {
	if(front3 == -1) {
		front3 = 0 ;
	}
	rear3 = rear3 + 1 ;
	queue3[rear3] = proc1 ;
}


void queue3Pop() {
	front3 = front3 + 1 ;
}


struct process queue3Front() {
	return queue3[front3] ;
}


void createProcess(int n, struct process proc1[]) {	
	int i ;
	for(i=0; i<n; i++) {
		printf("Enter Process ") ;
		scanf("%d",&proc1[i].process) ;
		printf("Enter Process Arrival Time") ;
		scanf("%d",&proc1[i].AT) ;
		printf("Enter Process Burst Time") ;
		scanf("%d",&proc1[i].BT) ;
		printf("Enter Processes Priority") ;
		scanf("%d",&proc1[i].P) ;
		proc1[i].RT= proc1[i].BT ;
	}
}


void assign(int n, struct process proc1[]) {
	int i ;
	for(i=0; i<n; i++) {
		if((proc1[i].P)>=0 && (proc1[i].P)<50) {
			queue1Push(proc1[i]) ;
		} else if ((proc1[i].P)>=50 && (proc1[i].P)<100) {
			queue2Push(proc1[i]) ;
		} else if ((proc1[i].P)>=100 && (proc1[i].P)<150) {
			queue3Push(proc1[i]) ;
		} 
	}	
}


void printQueueFront() {
	int i ;
	printf("Process in Queue 1 - ") ;
	for(i=0;i<=rear1;i++) {
		printf("P%d  ",queue1[i].process) ;
	}
	printf("\nProcess in Queue 2 - ") ;
	for(i=0;i<=rear2;i++) {
		printf("P%d  ",queue2[i].process) ;
	}
	printf("\nProcess in Queue 3 - ") ;
	for(i=0;i<=rear3;i++) {
		printf("P%d  ",queue3[i].process) ;
	}
	printf("\n") ;
}


void roundRobin(int n, struct process proc1[]) {
	int k,l,T,remain=n,Flag=0,TQ = 4,WT=0,TAT=0 ;
	
	printf("\n\nProcess\t\tWaiting Time    Turnaround Time\n\n"); 
  	for(T=0,k=0;remain!=0;) {  	 
	    if((proc1[k].RT<=TQ) && (proc1[k].RT)>0) { 
			T+=(proc1[k].RT); 
	      	(proc1[k].RT)=0; 
	      	Flag=1; 
	    } else if((proc1[k].RT)>0) { 
			(proc1[k].RT)-=TQ; 
			T+=TQ; 
	    } if((proc1[k].RT)==0 && Flag==1) { 
		    remain--; 
			printf("Process[%d]\t\t%d\t\t%d\n",proc1[k].process,T-((proc1[k].AT)-(proc1[k].BT)),T-(proc1[k].AT)); 
		    WT+=T-(proc1[k].AT)-(proc1[k].BT); 
			TAT+=T-(proc1[k].AT); 
		    Flag=0; 
	    } if(k==n-1) 
	    	k=0; 
	    else if((proc1[k+1].AT)<=T) 
	    	k++; 
	    else 
	    	k=0; 
	} 
	printf("\nAverage Waiting Time= %f\n",WT*1.0/n); 
	printf("Avg Turnaround Time = %f",TAT*1.0/n); 
}


void fcfs(int n, struct process proc1[]) {
	float AT1[500],WT1[500],TAT1[500];
	int k = 0 ;
    float aw_time1 = 0, atat_time1 = 0;
    WT1[0] = 0;
    TAT1[0] = queue3[front3].BT;
    AT1[0] = queue3[front3].BT+queue3[front3].AT;
    for( k = 1 ; k< n ; k++){
        AT1[k] = AT1[k-1] +proc1[k].BT;
        TAT1[k] = AT1[k] - proc1[k].AT;
        WT1[k] = TAT1[k] - proc1[k].BT;
    }
    for(k= 0 ; k< n ; k++){
        aw_time1 = aw_time1 + WT1[k];
        atat_time1 = atat_time1 + TAT1[k];
    }
    printf("\n\t\tWaiting Time    Turnaround Time\n");
    for(k= 0 ; k < n ; k++){
        printf("\nProcess[%d]\t\t%0.2f\t\t%0.2f\n",proc1[k].process,WT1[k],TAT1[k]);
    }
    //printf("\nAverage waiting time : %0.2f",aw_time1/n);
    //printf("\nAverage turn around time : %0.2f",atat_time1/n);       
}


/*void priorityScheduling(int n, struct process proc1[]) {
	int T = 0,largest ;
	struct process temp;
int k,l,sum_bt;
for(k=0;k<n-1;k++)
for(l=k+1;l<n;l++)
{
if(proc1[k].AT>proc1[l].AT)
{
temp=proc1[k];
proc1[k]=proc1[l];
proc1[l]=temp;
}
}
for(k=0;k<n;k++)
 {
 	proc1[k].processed=0;
 sum_bt+=proc1[k].BT;
 }
 proc1[rear2+1].P=-9999;
printf("\nProcess\t\tPriority\t\tWaiting Time\t\tTurnaround Time ");
  for(T=queue2[front2].AT;T<sum_bt;)
  {
    largest=rear2+1;
    for(k=0;k<n;k++)
    {
      if(proc1[k].AT<=T && proc1[k].processed!=1 && proc1[k].P>proc1[largest].P)
        largest=k;
    }
      T+=proc1[largest].BT;
      int ct[100],wt[100],tt[100] ;
  ct[largest]=T;
          wt[largest]=ct[largest]-proc1[largest].AT-proc1[largest].BT;
    tt[largest]=ct[largest]-proc1[largest].AT;
    proc1[largest].processed=1;
    //avgwt+=p[largest].wt;4
printf("\nProcess[%d]\t\t%d\t\t\t%d\t\t\t%d\t",proc1[largest].process,proc1[largest].P,wt[largest],tt[largest]);
}
//printf("\nAverage waiting time:%f\n",avgwt/n);
printf("\n") ;
}*/


void queuesche1() {
	roundRobin(rear1+1, queue1) ;
}
//void queueSch2() {
//	priorityScheduling(rear2+1, queue2) ;
//}
void queueS() {
	fcfs(rear3+1, queue3) ;
}

int main() {
	int n ;
	printf("How many process - ") ;
	scanf("%d",&n) ;
	struct process proc1[n] ;
	createProcess(n, proc1) ;
	assign(n, proc1) ;
	printQueueFront() ;
	queuesche1() ;
	//queueSch2() ;
	queueS() ;
}
