#include <iostream>
using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

int main()
{
    int n, timeQuantum;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[100];
    int i;

    for (i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        cout << "Enter arrival time of process " << p[i].id << ": ";
        cin >> p[i].arrivalTime;
        cout << "Enter burst time of process " << p[i].id << ": ";
        cin >> p[i].burstTime;
        p[i].remainingTime = p[i].burstTime;
        p[i].waitingTime = 0;
        p[i].turnaroundTime = 0;
    }

    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    int time = 0, completed = 0;
    int queue[100]; // stores process indices
    int front = 0, rear = 0;
    int visited[100] = {0}; // to check if already in queue

    // Add first processes which arrived at time 0
    for (i = 0; i < n; i++)
    {
        if (p[i].arrivalTime == 0)
        {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n)
    {
        if (front == rear)
        {
            // CPU is idle, move to next arrival
            time++;
            for (i = 0; i < n; i++)
            {
                if (p[i].arrivalTime <= time && visited[i] == 0)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (p[idx].remainingTime > timeQuantum)
        {
            p[idx].remainingTime -= timeQuantum;
            time += timeQuantum;
        }
        else
        {
            time += p[idx].remainingTime;
            p[idx].remainingTime = 0;
            completed++;
            p[idx].turnaroundTime = time - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
        }

        // Add newly arrived processes to queue
        for (i = 0; i < n; i++)
        {
            if (p[i].arrivalTime <= time && visited[i] == 0 && p[i].remainingTime > 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // Re-add current process if not finished
        if (p[idx].remainingTime > 0)
        {
            queue[rear++] = idx;
        }
    }

    float totalWT = 0, totalTAT = 0;

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (i = 0; i < n; i++)
    {
        cout << "P" << p[i].id << "\t" << p[i].arrivalTime << "\t" << p[i].burstTime
             << "\t" << p[i].waitingTime << "\t" << p[i].turnaroundTime << "\n";
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
    }

    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;

    return 0;
}