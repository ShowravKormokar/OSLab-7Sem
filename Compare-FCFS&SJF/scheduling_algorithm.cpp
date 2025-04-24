#include <iostream>
#include <iomanip>
#include "process.h"
#include "fcfs.h"
#include "sjf.h"

using namespace std;

int main()
{
    int n;
    Process processes[100];

    cout << "Enter number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter Arrival Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    double fcfsAvgTAT, fcfsAvgWT;
    fcfsScheduling(processes, n, fcfsAvgTAT, fcfsAvgWT);

    cout << "\n--- FCFS Scheduling ---\n";
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << fcfsAvgTAT << "\n";
    cout << "Average Waiting Time   : " << fixed << setprecision(2) << fcfsAvgWT << "\n";

    double sjfAvgTAT, sjfAvgWT;
    sjfScheduling(processes, n, sjfAvgTAT, sjfAvgWT);

    cout << "\n--- SJF Scheduling ---\n";
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << sjfAvgTAT << "\n";
    cout << "Average Waiting Time   : " << fixed << setprecision(2) << sjfAvgWT << "\n";

    cout << "\n--- Comparison ---\n";
    cout << (sjfAvgTAT < fcfsAvgTAT ? "SJF is better in terms of Turnaround Time.\n" : "FCFS is better in terms of Turnaround Time.\n");
    cout << (sjfAvgWT < fcfsAvgWT ? "SJF is better in terms of Waiting Time.\n" : "FCFS is better in terms of Waiting Time.\n");

    return 0;
}
