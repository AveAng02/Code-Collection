
#include <stdio.h>
#include <stdlib.h>


struct process
{
    int processID;
    int at;
    int bt;
};


struct processes
{
    int N;
    int* processID;
    int* at;
    int* bt;
};





void fifo(struct processes prosLst) {

    printf("\n\nFirst Come First Serve\n");

    int* ct = calloc(prosLst.N, sizeof(int));
    int* tat = calloc(prosLst.N, sizeof(int));
    int* wt = calloc(prosLst.N, sizeof(int));

    float avgtat = 0.0;
    float avgwt = 0.0;

    // Completion time calculation
    ct[0] = prosLst.bt[0];

    for(int i = 1; i < prosLst.N; i++) {

        if(ct[i - 1] < prosLst.at[i]) {

            ct[i] = prosLst.at[i] + prosLst.bt[i];
        }
        else {
            ct[i] = ct[i - 1] + prosLst.bt[i];
        }
    }

    // Calculation Turn Around Time
    for(int i = 0; i < prosLst.N; i++) {
        tat[i] = ct[i] - prosLst.at[0];

        avgtat += tat[i];
    }

    // Calculation of waiting time
    for(int i = 0; i < prosLst.N; i++) {
        wt[i] = tat[i] - prosLst.bt[i];

        avgwt += wt[i];
    }

    avgtat /= prosLst.N;
    avgwt /= prosLst.N;

    printf("| PID | AT | BT | CT | TAT | WT |\n");

    for(int i = 0; i < prosLst.N; i++) {
        printf("|  %d  | %d | %d | %d | %d | %d |\n", prosLst.processID[i], prosLst.at[i], prosLst.bt[i], ct[i], tat[i], wt[i]);
    }

    printf(" Average Turn Around Time : %f\n", avgtat);
    printf(" Average Waiting Time : %f\n", avgwt);

}

int isEmpty(struct process newLst[], int N) {

    for(int i = 0; i < N; i++) {

        if(newLst[i].processID != -1) {
            return 0;
        }
    }

    return 1;
}

int shortestTime(struct process newLst[], int N) {

    int id = 0;

    for(int i = 0; i < N; i++) {
        if(newLst[id].bt > newLst[i].bt && newLst[i].processID != -1) {
            id = i;
        }
    }

    return id;
}

void addProcess(struct process newLst[], int N, int id_, int at_, int bt_) {

    int id = 0;

    for(int i = 0; i < N; i++) {
        if(newLst[i].processID == -1) {
            id = i;
            break;
        }
    }

    newLst[id].at = at_;
    newLst[id].bt = bt_;
    newLst[id].processID = id_;
}

void srtf(struct processes prosLst) {

    printf("\n\nShortest Remaining Time First\n");

    int time = 0;

    int* ct = calloc(prosLst.N, sizeof(int));
    int* tat = calloc(prosLst.N, sizeof(int));
    int* wt = calloc(prosLst.N, sizeof(int));
    int* visited = calloc(prosLst.N, sizeof(int));

    float avgtat = 0.0;
    float avgwt = 0.0;

    struct process* newLst = calloc(prosLst.N, sizeof(struct process));

    addProcess(newLst, prosLst.N, prosLst.processID[0], prosLst.at[0], prosLst.bt[0]);
    visited[0] = 1;

    for(int i = 0; i < prosLst.N; i++) {
        printf("PID : %d ; AT : %d ; BT : %d\n", newLst[i].processID, newLst[i].at, newLst[i].bt);
    }

    for(int i = 1; i < prosLst.N; i++) {
        newLst[i].processID = -1;
    }

    while(!isEmpty(newLst, prosLst.N)) { // the new process list is not empty

        // select the process with the smallest burst time
        int shortestID = shortestTime(newLst, prosLst.N);

        // simulate process execution time that is reduce burst time
        newLst[shortestID].bt--;

        // check if process is complete
        if(newLst[shortestID].bt == 0) {
            int pos = 0;

            for(int i = 0; i < prosLst.N; i++) {
                if(newLst[shortestID].processID == prosLst.processID[i]) {
                    pos = i;
                    break;
                }
            }

            // if process is complete record completion time
            ct[pos] = time;

            // remove the process from the list
            newLst[shortestID].processID = -1;

            printf("Removing a completed process\n");
            for(int i = 0; i < prosLst.N; i++) {
                printf("PID : %d ; AT : %d ; BT : %d\n", newLst[i].processID, newLst[i].at, newLst[i].bt);
            }
        }

        // if arrival time of process is equal to current time then add the new process to the process list
        for(int i = 0; i < prosLst.N; i++) {
            if(time == prosLst.at[i]) {
                addProcess(newLst, prosLst.N, prosLst.processID[i], prosLst.at[i], prosLst.bt[i]);

                printf("Adding a new process\n");
                for(int i = 0; i < prosLst.N; i++) {
                    printf("PID : %d ; AT : %d ; BT : %d\n", newLst[i].processID, newLst[i].at, newLst[i].bt);
                }

                visited[i] = 1;
            }
        }

        // increment to the next time slice
        // printf("time updated\n");
        time++;
    }


    
    // Calculation Turn Around Time
    for(int i = 0; i < prosLst.N; i++) {
        tat[i] = ct[i] - prosLst.at[0];

        avgtat += tat[i];
    }

    // Calculation of waiting time
    for(int i = 0; i < prosLst.N; i++) {
        wt[i] = tat[i] - prosLst.bt[i];

        avgwt += wt[i];
    }

    avgtat /= prosLst.N;
    avgwt /= prosLst.N;

    printf("| PID | AT | BT | CT | TAT | WT |\n");

    for(int i = 0; i < prosLst.N; i++) {
        printf("|  %d  | %d | %d | %d | %d | %d |\n", prosLst.processID[i], prosLst.at[i], prosLst.bt[i], ct[i], tat[i], wt[i]);
    }

    printf(" Average Turn Around Time : %f\n", avgtat);
    printf(" Average Waiting Time : %f\n", avgwt);


}


int main() {

    struct processes pros;

    pros.N = 5;

    int processID[] = {0, 1, 2, 3, 4};
    int arrival[] = {2,5,1,0,4};
    int burst[] = {6,2,8,3,4};

    pros.processID = processID;
    pros.at = arrival;
    pros.bt = burst;

    // Bubble Sort
    for(int i = 0, j = 0; i < pros.N - 1; i++) {

        for(j = 0; j < (pros.N - i - 1); j++) {

            if(pros.at[j] > pros.at[j + 1]) {

                int tempprocessID = pros.processID[j];
                int tempat = pros.at[j];
                int tempbt = pros.bt[j];

                pros.processID[j] = pros.processID[j + 1];
                pros.at[j] = pros.at[j + 1];
                pros.bt[j] = pros.bt[j + 1];

                pros.processID[j + 1] = tempprocessID;
                pros.at[j + 1] = tempat;
                pros.bt[j + 1] = tempbt;
            }

        }

    }

    fifo(pros);

    srtf(pros);

    return 0;
}


