#ifndef FCFS_H
#define FCFS_H

#include "process.h"

void fcfsScheduling(Process p[], int n, double &avgTAT, double &avgWT)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].arrivalTime > p[j].arrivalTime)
            {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int currentTime = 0;
    int totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++)
    {
        if (currentTime < p[i].arrivalTime)
        {
            currentTime = p[i].arrivalTime;
        }
        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
        currentTime = p[i].completionTime;

        totalTAT += p[i].turnaroundTime;
        totalWT += p[i].waitingTime;
    }

    avgTAT = (double)totalTAT / n;
    avgWT = (double)totalWT / n;
}

#endif
