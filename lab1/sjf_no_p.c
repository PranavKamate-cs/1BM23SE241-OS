
/*  SLF non preemtive cpu scheduling aigorithom */
#include<stdio.h>
#define MAX 100
int p[MAX], bt[MAX], at[MAX], tat[MAX], wt[MAX], ct[MAX], n;
void sort();
void fcfs();
void display();
void main(){
    printf("Enter the number of process:");
    scanf("%d",&n);
    printf("Enter the process data:\n\n");
    for (int i=0 ; i<n ; i++){
        printf("process no.:");
        scanf("%d",&p[i]);
        printf("process AT:");
        scanf("%d",&at[i]);
        printf("process BT:");
        scanf("%d",&bt[i]);
    }
    sort();
    sjf_non_p();
    int sumTAT = 0, sumWT=0;
    for(int i=0; i<n ; i++){
        sumTAT=sumTAT + tat[i];
        sumWT=sumWT + wt[i];
    }
    int avgTAT=sumTAT/n , avgWT = sumWT/n;
    display();
    printf("\nThe avg TAT = %d\nThe avg WT = %d\n",avgTAT,avgWT);
}

void sort(){
    for (int i=0; i<n ; i++){
        for (int j=i+1; j<n ; j++){
            if (bt[i] > bt[j]){
                int temp = at[i];
                at[i]=at[j];
                at[j]=temp;
                temp = p[i];
                p[i]=p[j];
                p[j]=temp;
                temp = bt[i];
                bt[i]=bt[j];
                bt[j]=temp;
            }
        }
    }
}

void sjf_non_p(){
    int pt=0;
    for (int i=0 ; i<n ;i++){
        pt = pt + bt[i];
        if(pt<at[i]){
            pt=at[i];
        }
        ct[i] = pt;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

void display(){
    printf("\nProcess  AT\tBT\tCT\tTAT\tWT\n");
    for (int i=0; i<n ; i++){
        printf("%d\t %d\t%d\t%d\t%d\t%d\t\n", p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }
}