#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void calculateTimes(Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        current_time = processes[i].completion_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

void sortByArrival(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        processes[i].process_id = i + 1;
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    sortByArrival(processes, n);

    calculateTimes(processes, n);

    printf("\nProcess ID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d         | %d            | %d         | %d               | %d               | %d\n",
               processes[i].process_id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    return 0;
}

