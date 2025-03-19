
/*  preemptive priority , non-preemptive priority, Round Robin cpu scheduling aigorithom */
#include<stdio.h>
#define MAX 100
int p[MAX], bt[MAX],pr[MAX], at[MAX], tat[MAX], wt[MAX], ct[MAX], n,Q;
void sort();
void PreemptivePreority();
void non_preemptivePreority();
void RoundRobin();
void display();
void display_avg();
void swap(int* a,int* b);
void main(){
   int ch;
   printf("Enter\n1)to enter values\n2)PreemptivePreority\n3)non_preemptivePreority\n4)RoundRobin\n5)Exit\n");
   do{
    printf("\nEnter your choice:");
    scanf("%d",&ch);
    switch(ch){
        case 1:{
            printf("Enter the number of process:");
            scanf("%d",&n);
            printf("Enter the process data:\n\n");
                for (int i=0 ; i<n ; i++){
                    printf("process %d AT:",i);
                    scanf("%d",&at[i]);
                    printf("process %d BT:",i);
                    scanf("%d",&bt[i]);
                    printf("process %d priority:",i);
                    scanf("%d",&pr[i]);
                }
        }
        case 2:{
            printf("cpu scheduling for PreemptivePreority\n");
            PreemptivePreority();
            break;
        }
        case 3:{
            printf("cpu scheduling for non_PreemptivePreority\n");
            non_preemptivePreority();
            break;
        }
        case 4:{
            printf("cpu scheduling for RoundRobin\n");
            RoundRobin();
            break;
        }
        case 5:{
            printf("Exiting !!");
            break;
        }
    }
   }while(ch!=5);
}

void sort(){
    for (int i=0; i<n ; i++){
        for (int j=i+1; j<n ; j++){
            if (at[i] < at[j]){
                swap(&p[i],&p[j]);
                swap(&bt[i],&bt[j]);
                swap(&at[i],&at[j]);
                swap(&pr[i],&pr[j]);
            }
        }
    }
}

void swap(int* a, int*b){
    int t = *a;
    *a = *b;
    *b = t;
}

void display(){
    printf("\nProcess  AT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i=0; i<n ; i++){
        printf("%d\t %d\t%d\t%d\t%d\t%d\t%d\t\n", p[i],at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);
    }
}

void display_avg(){
    int sumTAT = 0, sumWT=0;
    for(int i=0; i<n ; i++){
        sumTAT=sumTAT + tat[i];
        sumWT=sumWT + wt[i];
    }
    int avgTAT=sumTAT/n , avgWT = sumWT/n;
    display();
    printf("\nThe avg TAT = %d\nThe avg WT = %d\n",avgTAT,avgWT);
}

void PreemptivePreority(){
    int completed = 0, time = 0, min_priority, min_index;
    int r[MAX];
    sort();
    for (int i = 0; i < n; i++) r[i] = bt[i];

    while (completed < n) {
        min_priority = 9999;
        min_index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && r[i] > 0 && pr[i] < min_priority) {
                min_priority = pr[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        r[min_index]--;
        time++;

        if (r[min_index] == 0) {
            completed++;
            ct[min_index] = time;
            tat[min_index] = ct[min_index] - at[min_index];
            wt[min_index] = tat[min_index] - bt[min_index];
        }
    }
    display();
    display_avg();
}

void non_preemptivePreority(){
    int completed = 0, time = 0, min_priority, min_index;
    int completedFlag[MAX] = {0};
    sort();
    sortByArrival(n, at, bt, pr, ct);
    while (completed < n) {
        min_priority = 9999;
        min_index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && completedFlag[i] == 0 && pr[i] < min_priority) {
                min_priority = pr[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        time += bt[min_index];
        ct[min_index] = time;
        tat[min_index] = ct[min_index] - at[min_index];
        wt[min_index] = tat[min_index] - bt[min_index];
        completedFlag[min_index] = 1;
        completed++;
    }
    display();
    display_avg();
}

void RoundRobin(){
    int remaining[MAX], ct[MAX], tat[MAX], wt[MAX];
    int time = 0, completed = 0;
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
    display();
    display_avg();
}