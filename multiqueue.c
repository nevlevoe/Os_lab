#include <stdio.h>
#include <limits.h>

struct Process {
    int id;     // Process ID
    int burstTime; // Burst time of the process
    int arrivalTime; // Arrival time of the process
    int queueType; // Queue type (1 for system process, 2 for user process)
    int waitingTime; // Waiting time of the process
    int turnAroundTime; // Turnaround time of the process
    int responseTime; // Response time of the process
    int startTime; // Start time of the process
    int endTime; // End time of the process
    int visited; // Flag to check if the process is visited
};
void main() {
    int numProcesses, currentTime = 0;
    float averageWaitingTime = 0, averageTurnAroundTime = 0, averageResponseTime = 0, throughput;

    // User prompt and input
    printf("Queue 1 is system process\nQueue 2 is User Process\n");
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];
    struct Process tempProcess;

    for(int i = 0; i < numProcesses; i++) {
        processes[i].id = i + 1;
        processes[i].visited = 0;
        printf("Enter Burst Time, Arrival Time and Queue of P%d: ", i + 1);
        scanf("%d %d %d", &processes[i].burstTime, &processes[i].arrivalTime, &processes[i].queueType);
    }

    // Sorting based on Arrival Time and Queue Type
    for(int i = 0; i < numProcesses; i++) {
        for(int j = i + 1; j < numProcesses; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime ||
                (processes[i].arrivalTime == processes[j].arrivalTime && processes[i].queueType > processes[j].queueType)) {
                tempProcess = processes[i];
                processes[i] = processes[j];
                processes[j] = tempProcess;
            }
        }
    }

    // Scheduling logic
    int completedTime = processes[0].burstTime;
    int minQueueType = INT_MAX, minQueueIndex, processCount = 0;
    processes[0].visited = 1;

    while (processCount < numProcesses - 1) {
        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].arrivalTime <= completedTime && processes[i].visited == 0) {
                if (processes[i].queueType < minQueueType) {
                    minQueueType = processes[i].queueType;
                    minQueueIndex = i;
                }
            }
        }

        processes[minQueueIndex].visited = 1;
        completedTime += processes[minQueueIndex].burstTime;
        minQueueType = INT_MAX;

        tempProcess = processes[processCount + 1];
        processes[processCount + 1] = processes[minQueueIndex];
        processes[minQueueIndex] = tempProcess;

        processCount++;
    }

    // Calculating and displaying times
    printf("\nProcess\tWaiting Time\tTurn Around Time\tResponse Time\n");
    for(int i = 0; i < numProcesses; i++) {
        if (processes[i].arrivalTime < currentTime) {
            processes[i].startTime = currentTime;
        } else {
            processes[i].startTime = processes[i].arrivalTime;
        }
        processes[i].endTime = processes[i].startTime + processes[i].burstTime;
        currentTime += processes[i].burstTime;

        processes[i].turnAroundTime = processes[i].endTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
        processes[i].responseTime = processes[i].startTime - processes[i].arrivalTime;

        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].waitingTime, processes[i].turnAroundTime, processes[i].responseTime);

        averageWaitingTime += processes[i].waitingTime;
        averageTurnAroundTime += processes[i].turnAroundTime;
        averageResponseTime += processes[i].responseTime;
    }

    throughput = (float)processes[numProcesses - 1].endTime / numProcesses;
    printf("Average Waiting Time: %.2f\n", averageWaitingTime / numProcesses);
    printf("Average Turn Around Time: %.2f\n", averageTurnAroundTime / numProcesses);
    printf("Average Response Time: %.2f\n", averageResponseTime / numProcesses);
    printf("Throughput: %.2f", throughput);
}
