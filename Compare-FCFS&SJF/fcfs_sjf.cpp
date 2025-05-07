#include <iostream>
using namespace std;

#define MAX 100

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

// Function to copy original burst times
void copyBurstTimes(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Function to calculate average TAT and WT
void calculateAvg(int n, int wt[], int tat[], float& avgWT, float& avgTAT) {
    int totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    avgWT = (float)totalWT / n;
    avgTAT = (float)totalTAT / n;
}

// First-Come, First-Serve Scheduling
void fcfs(Process p[], int n, float& avgWT, float& avgTAT) {
    int wt[MAX], tat[MAX], startTime[MAX];
    wt[0] = 0;
    startTime[0] = p[0].arrivalTime;

    for (int i = 1; i < n; i++) {
        startTime[i] = startTime[i - 1] + p[i - 1].burstTime;
        if (startTime[i] < p[i].arrivalTime)
            startTime[i] = p[i].arrivalTime;
        wt[i] = startTime[i] - p[i].arrivalTime;
    }

    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + p[i].burstTime;
    }

    calculateAvg(n, wt, tat, avgWT, avgTAT);
}

// Shortest Job First (Preemptive)
void sjfPreemptive(Process p[], int n, float& avgWT, float& avgTAT) {
    int time = 0, complete = 0, minBurst = 1e9;
    int shortest = -1, finishTime;
    bool check = false;
    int bt[MAX], wt[MAX], tat[MAX];
    bool isDone[MAX] = {false};

    // Copy original burst times
    for (int i = 0; i < n; i++) {
        bt[i] = p[i].burstTime;
        wt[i] = 0;
    }

    int remaining[MAX];
    for (int i = 0; i < n; i++) {
        remaining[i] = bt[i];
    }

    while (complete != n) {
        minBurst = 1e9;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= time && remaining[i] > 0 && remaining[i] < minBurst) {
                minBurst = remaining[i];
                shortest = i;
                check = true;
            }
        }

        if (!check) {
            time++;
            continue;
        }

        remaining[shortest]--;
        if (remaining[shortest] == 0) {
            complete++;
            finishTime = time + 1;
            tat[shortest] = finishTime - p[shortest].arrivalTime;
            wt[shortest] = tat[shortest] - p[shortest].burstTime;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        time++;
        check = false;
    }

    calculateAvg(n, wt, tat, avgWT, avgTAT);
}


int main() {
    int n;
    Process processes[MAX];

    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    // Sort processes by arrival time for consistency
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    float avgWT_FCFS = 0, avgTAT_FCFS = 0;
    float avgWT_SJF = 0, avgTAT_SJF = 0;

    fcfs(processes, n, avgWT_FCFS, avgTAT_FCFS);
    sjfPreemptive(processes, n, avgWT_SJF, avgTAT_SJF);

    cout << "\n--- FCFS Scheduling ---";
    cout << "\nAverage Waiting Time: " << avgWT_FCFS;
    cout << "\nAverage Turnaround Time: " << avgTAT_FCFS;

    cout << "\n\n--- SJF (Preemptive) Scheduling ---";
    cout << "\nAverage Waiting Time: " << avgWT_SJF;
    cout << "\nAverage Turnaround Time: " << avgTAT_SJF;

    cout << "\n\n--- Comparison Result ---\n";
    if (avgWT_SJF < avgWT_FCFS) {
        cout << "SJF (Preemptive) is better in terms of average waiting time.\n";
    } else if (avgWT_SJF > avgWT_FCFS) {
        cout << "FCFS is better in terms of average waiting time.\n";
    } else {
        cout << "Both algorithms have equal average waiting time.\n";
    }

    return 0;
}
