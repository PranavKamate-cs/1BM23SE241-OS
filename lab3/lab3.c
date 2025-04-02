#include<stdio.h>

#define MAX 100
int sp[MAX],sbt[MAX],sat[MAX],up[MAX],ubt[MAX],uat[MAX],tat[MAX],ct[MAX],wt[MAX];
int n,u,s;
void FCFS(int p[],int bt[],int at[], int d);
void RoundRobin(int p[],int bt[], int at[], int d);
void sort(int p[], int at[], int bt[], int d);
void swap(int* a,int* b);
void display(int p[], int at[], int bt[], int ct[], int tat[], int wt[], int d );

void sort(int p[], int at[], int bt[], int d){
    for (int i=0; i<d ; i++){
        for (int j=i+1; j<d ; j++){
            if (at[i] < at[j]){
                swap(&p[i],&p[j]);
                swap(&bt[i],&bt[j]);
                swap(&at[i],&at[j]);
            }
        }
    }
}

void swap(int* a, int*b){
    int t = *a;
    *a = *b;
    *b = t;
}

void display(int p[], int at[], int bt[], int ct[], int tat[], int wt[], int d ){
    float avgTAT=0, avgWT=0;
    printf("\nProcess  AT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i=0; i<n ; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t\n", p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
        avgTAT += tat[i];
        avgWT += wt[i];
    }
    avgTAT = avgTAT/d;
    avgWT = avgWT/d;
    printf("\nThe avg TAT = %f\nThe avg WT = %f\n",avgTAT,avgWT);
}

void FCFS(int p[],int bt[],int at[], int d){
    sort(p,at,bt,d);
    int time=0;
    for (int i=0 ; i<n ;i++){
        if(time<=at[i]){
            time=at[i];
        }
        time = time + bt[i];
        ct[i] = time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    printf("cpu scheduling for FCFS\n");
    display(p,at,bt,ct,tat,wt,d);
}

void RoundRobin(int p[],int bt[], int at[], int d){
    int remaining[MAX], ct[MAX], tat[MAX], wt[MAX];
    int time = 0, completed = 0,Q;
    printf("\nEntre the time quantum:");
    scanf("%d",&Q);
    for (int i = 0; i < n; i++) remaining[i] = bt[i];
    while (completed < n) {
        int all_idle = 1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && at[i] <= time) {
                all_idle = 0;
                if (remaining[i] > Q) {
                    time += Q;
                    remaining[i] -= Q;
                } else {
                    time += remaining[i];
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    remaining[i] = 0;
                    completed++;
                }
            }
        }

        if (all_idle)
            time++;
    }
    display(p,at,bt,ct,tat,wt,d);
}