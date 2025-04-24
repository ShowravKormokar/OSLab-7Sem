#ifndef SJF_H
#define SJF_H

#include "process.h"

// Function to perform Preemptive SJF (Shortest Remaining Time First) Scheduling
void sjfScheduling(Process p[], int n, double &avgTAT, double &avgWT)
{
    int remainingTime[100];       // Array to track remaining burst time of each process
    bool isCompleted[100] = {0};  // Track completion status of processes

    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = p[i].burstTime; // Initialize remaining time
    }

    int completed = 0;
    int currentTime = 0;
    int totalTAT = 0, totalWT = 0;
    int minIndex = -1;
    int minRemaining = 9999;

    while (completed < n)
    {
        minIndex = -1;
        minRemaining = 9999;

        // Find process with shortest remaining time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && p[i].arrivalTime <= currentTime && remainingTime[i] < minRemaining && remainingTime[i] > 0)
            {
                minRemaining = remainingTime[i];
                minIndex = i;
            }
        }

        if (minIndex == -1)
        {
            currentTime++; // CPU idle
            continue;
        }

        // Process runs for 1 unit of time
        remainingTime[minIndex]--;
        currentTime++;

        // If process is finished
        if (remainingTime[minIndex] == 0)
        {
            isCompleted[minIndex] = true;
            completed++;

            p[minIndex].completionTime = currentTime;
            p[minIndex].turnaroundTime = p[minIndex].completionTime - p[minIndex].arrivalTime;
            p[minIndex].waitingTime = p[minIndex].turnaroundTime - p[minIndex].burstTime;

            totalTAT += p[minIndex].turnaroundTime;
            totalWT += p[minIndex].waitingTime;
        }
    }

    avgTAT = (double)totalTAT / n;
    avgWT = (double)totalWT / n;
}

#endif // End of include guard
