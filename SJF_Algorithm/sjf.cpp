#include <iostream>  // For input and output
#include <vector>    // For using vector container
#include <algorithm> // For sort function
#include <iomanip>   // For controlling output format (like setprecision)

using namespace std;

// Structure to store process information
struct Process
{
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
    bool done;      // To check if the process is already completed

    // Constructor to initialize a process
    Process(int id, int at, int bt)
    {
        pid = id;
        arrival = at;
        burst = bt;
        done = false;
    }
};

// Comparator function to sort processes based on arrival time
bool compareArrival(const Process &a, const Process &b)
{
    return a.arrival < b.arrival;
}

int main()
{
    int n; // Number of processes
    cout << "Enter number of processes: ";
    cin >> n; // Take number of processes as input

    vector<Process> processes; // Vector to store all processes

    // Input arrival and burst time for each process
    for (int i = 0; i < n; ++i)
    {
        int at, bt;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> at >> bt;                       // Read arrival and burst time
        processes.emplace_back(i + 1, at, bt); // Add process to the vector
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0;                         // Keeps track of current time of CPU
    int completed = 0;                           // Counts number of completed processes
    float totalWaiting = 0, totalTurnaround = 0; // For calculating average

    // Continue until all processes are completed
    while (completed < n)
    {
        int idx = -1;       // Index of the selected process
        int minBurst = 1e9; // Minimum burst time found so far (initially very high)

        // Find the process with the shortest burst time among those that have arrived
        for (int i = 0; i < n; ++i)
        {
            if (!processes[i].done && processes[i].arrival <= currentTime)
            {
                if (processes[i].burst < minBurst)
                {
                    minBurst = processes[i].burst;
                    idx = i; // Store the index of the process with the shortest burst
                }
            }
        }

        // If a valid process is found
        if (idx != -1)
        {
            processes[idx].completion = currentTime + processes[idx].burst;                 // Calculate completion time
            processes[idx].turnaround = processes[idx].completion - processes[idx].arrival; // Turnaround = CT - AT
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;      // Waiting = TAT - BT

            totalWaiting += processes[idx].waiting;       // Add to total waiting time
            totalTurnaround += processes[idx].turnaround; // Add to total turnaround time

            currentTime = processes[idx].completion; // Update current time to after this process completes
            processes[idx].done = true;              // Mark this process as done
            completed++;                             // Increment number of completed processes
        }
        else
        {
            currentTime++; // If no process is ready, increment time (CPU idle)
        }
    }

    // Display table header
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";

    // Display process information
    for (const auto &p : processes)
    {
        cout << "P" << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion
             << "\t" << p.turnaround << "\t" << p.waiting << "\n";
    }

    // Set output to 2 decimal places
    cout << fixed << setprecision(2);

    // Print average waiting and turnaround times
    cout << "\nAverage Waiting Time: " << totalWaiting / n;
    cout << "\nAverage Turnaround Time: " << totalTurnaround / n << "\n";

    return 0; // Program ends
}
