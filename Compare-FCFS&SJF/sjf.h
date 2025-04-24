#ifndef SJF_H // Start of include guard for the SJF header
#define SJF_H // Define a unique macro to avoid multiple inclusions

#include "process.h" // Include the shared Process structure definition

// Function to perform SJF (Shortest Job First) Scheduling
void sjfScheduling(Process p[], int n, double &avgTAT, double &avgWT)
{
    Process temp[100]; // Create a copy of the original process array to work on
    for (int i = 0; i < n; i++)
    {
        temp[i] = p[i]; // Copy each process from input to temp array
    }

    int completed = 0;          // Counter for number of processes completed
    int currentTime = 0;        // Keeps track of current CPU time
    int totalTAT = 0;           // Accumulator for total Turnaround Time
    int totalWT = 0;            // Accumulator for total Waiting Time
    bool isDone[100] = {false}; // Boolean array to mark if a process has been completed

    // Loop until all processes are completed
    while (completed < n)
    {
        int idx = -1;        // Index of the selected process for current scheduling
        int minBurst = 9999; // Store minimum burst time found (initialized to a high value)

        // Find the process with the shortest burst time among the arrived processes
        for (int i = 0; i < n; i++)
        {
            if (!isDone[i] && temp[i].arrivalTime <= currentTime && temp[i].burstTime < minBurst)
            {
                minBurst = temp[i].burstTime; // Update the minimum burst time
                idx = i;                      // Update the index of the selected process
            }
        }

        // If no process has arrived yet, increment the current time (CPU is idle)
        if (idx == -1)
        {
            currentTime++;
        }
        else
        {
            // Set the selected process's completion time
            temp[idx].completionTime = currentTime + temp[idx].burstTime;

            // Calculate turnaround time = completion time - arrival time
            temp[idx].turnaroundTime = temp[idx].completionTime - temp[idx].arrivalTime;

            // Calculate waiting time = turnaround time - burst time
            temp[idx].waitingTime = temp[idx].turnaroundTime - temp[idx].burstTime;

            // Move time forward to the process's completion time
            currentTime = temp[idx].completionTime;

            // Mark this process as completed
            isDone[idx] = true;
            completed++; // Increment number of completed processes

            // Add to total turnaround time and waiting time
            totalTAT += temp[idx].turnaroundTime;
            totalWT += temp[idx].waitingTime;
        }
    }

    // Calculate average turnaround time and waiting time
    avgTAT = (double)totalTAT / n;
    avgWT = (double)totalWT / n;
}

#endif // End of include guard
