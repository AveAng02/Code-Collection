
// SRTF Scheduling 

#include <stdio.h>
#include <stdlib.h>


struct process {
    int pid;
    int at;
    int bt;
    int tl;
};

int completed(int* processing, int pNum) {

    for(int i = 0; i < pNum; i++) {
        if(processing[i] == 1) {
            return 0;
        }
    }

    return 1;
}

int shortestTimeLeft(struct process* prsList, int* processing, int pNum) {

    int prosID = 0;

    for(int i = 0; i < pNum; i++) {

        if(processing[i] == 1) {

            prosID = i;
            break;
        }
    }

    for(int i = 0; i < pNum; i++) {

        if(processing[i] == 1) {

            if(prsList[prosID].tl > prsList[i].tl) {
                prosID = i;
            }
        }
    }

    return prosID;
}

void srtf(struct process* prsList, int pNum) {

    double atat = 0.0;
    double awt = 0.0;
    int time = 0;
    int* ct = calloc(pNum, sizeof(int));
    int* tat = calloc(pNum, sizeof(int));
    int* wt = calloc(pNum, sizeof(int));
    int* processing = calloc(pNum, sizeof(int));
    int currentID = 0;

    for(int i = 0; i < pNum; i++) {
        if(prsList[i].at == 0) {
            processing[i] = 1; // starting the processes that arrive first
        }
    }

    // Completion time calculation block

    while(!completed(processing, pNum)) {

        // fetching the shortest time ID
        currentID = shortestTimeLeft( prsList, processing, pNum);
        prsList[currentID].tl--;
        time++;

        // logging completion time of process 
        if(prsList[currentID].tl == 0) {
            processing[currentID] = 0;
            ct[currentID] = time;
        }

        for(int i = 0; i < pNum; i++) {
            if(prsList[i].at == time) {
                processing[i] = 1;
            }
        }

        printf("Time : %d       ID : %d\n", time, currentID + 1);
    }

    // Average turn around time calculation
    for(int i = 0; i < pNum; i++) {
        tat[i] = ct[i] - prsList[i].at;
        atat += tat[i];
    }

    atat /= pNum;

    // average waiting time calculation
    for(int i = 0; i < pNum; i++) {
        wt[i] = tat[i] - prsList[i].bt;
        awt += wt[i];
    }

    awt /= pNum;

    printf("Average Turn Around Time : %.2f\n", atat);
    printf("Average Waiting Time : %.2f\n", awt);
}


int main() {

    int n = 0;
    struct process* prsList;

    scanf("%d", &n);

    prsList = calloc(n, sizeof(struct process));

    printf("Enter Arrival Time :\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &prsList[i].at);
    } 

    printf("Enter Burst Time :\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &prsList[i].bt);
        prsList[i].tl = prsList[i].bt;
    } 

    srtf(prsList, n);

    return 0;
}

