#include <iostream>
#include <iomanip> // For formatting output

using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

int main()
{
    int numProcesses;

    // Taking number of processes as input
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    Process processes[100]; // static array to avoid vector usage (per your earlier constraint)

    // Taking Arrival Time and Burst Time input
    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter Arrival Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    // Sorting the processes based on Arrival Time
    for (int i = 0; i < numProcesses - 1; i++)
    {
        for (int j = i + 1; j < numProcesses; j++)
        {
            if (processes[i].arrivalTime > processes[j].arrivalTime)
            {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // FCFS Scheduling Algorithm
    int currentTime = 0;
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    for (int i = 0; i < numProcesses; i++)
    {
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime; // Handle CPU idle time
        }

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    // Output the results in a formatted table
    cout << "\n---------------------------------------------------------------------------------------------------\n";
    cout << "Process ID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n";
    cout << "---------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < numProcesses; i++)
    {
        cout << "P" << setw(13) << left << processes[i].id
             << setw(17) << processes[i].arrivalTime
             << setw(15) << processes[i].burstTime
             << setw(19) << processes[i].completionTime
             << setw(17) << processes[i].turnaroundTime
             << processes[i].waitingTime << endl;
    }

    double averageTurnaroundTime = (double)totalTurnaroundTime / numProcesses;
    double averageWaitingTime = (double)totalWaitingTime / numProcesses;

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << averageTurnaroundTime << " units" << endl;
    cout << "Average Waiting Time: " << averageWaitingTime << " units" << endl;

    return 0;
}
