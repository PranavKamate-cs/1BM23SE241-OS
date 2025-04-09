#include <stdio.h>
#include<stdbool.h>
#include <math.h>
#define MAX 100


int execution_time[MAX],period[MAX],deadline[MAX],d[MAX],r[MAX],id[MAX],n,LCM;

int lcm(int a, int b) {
    int max = (a > b) ? a : b;
    while (1) {
        if (max % a == 0 && max % b == 0)
            return max;
        max++;
    }
}

bool schedule(){
    float r = 0.0;
    for (int i = 0; i < n; i++) {
        r += (float)execution_time[i] / (float)period[i];
    }
    float bound = n * (pow(2.0, 1.0 / n) - 1);

    printf("Utilization: %.4f <= Bound: %.4f : %s\n", r, bound, (r <= bound) ? "True" : "False");

    return (r <= bound);
}

int main (){
    printf("Enter the number of processes :");
    scanf("%d",&n);
    printf("Enter the CPU burst time:\n");
    for (int i=0; i<n; i++){
        scanf("%d",&execution_time[i]);
        id[i]=i+1;
    }
    printf("Enter the period:\n");
    for (int i=0; i<n; i++){
        scanf("%d",&period[i]);
    }
    printf("Enter the deadline:\n");
    for (int i=0; i<n; i++){
        scanf("%d",&deadline[i]);
    }

    printf("--Earliest Deadline First Scheduling--");
    printf("\nProcess\tBurst\tPeriod\n");
    for(int i=0;i<n;i++){
        printf("%d\t\t%d\t\t%d\n",id[i],execution_time[i],period[i]);
    }
    LCM=period[0];
    for (int i=1; i<n;i++){
        LCM=lcm(LCM, period[i]);
    }
    printf("\nLCM : %d\n",LCM);
    if(schedule()){
        EDF();
    }
    return 0;
}

void EDF(){
    for (int i = 0; i < n; i++) {
        r[i] = 0;
        d[i] = deadline[i];
    }

    for (int t = 0; t < LCM; t++) {
        int current = -1;

        for (int i = 0; i < n; i++) {
            if (t % period[i] == 0) {
                r[i] = execution_time[i];
                d[i] = t + deadline[i];
            }

            if (r[i] > 0 &&
                (current == -1 || d[i] < d[current]))
                current = i;
        }

        if (current != -1) {
            printf("Time %d: Task %d\n", t, id[current]);
            r[current]--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }

}