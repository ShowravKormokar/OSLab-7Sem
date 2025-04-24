#ifndef PROCESS_H // Start of include guard to prevent double inclusion of this header file
#define PROCESS_H // Define a unique macro to check if this file is already included

// Definition of the Process structure
struct Process
{
    int id;             // Unique identifier for the process (e.g., P1, P2, etc.)
    int arrivalTime;    // Time at which the process arrives and is ready for execution
    int burstTime;      // Time required by the process to execute completely (CPU time needed)
    int completionTime; // Time at which the process finishes its execution
    int turnaroundTime; // Total time taken from arrival to completion (completionTime - arrivalTime)
    int waitingTime;    // Time the process spends waiting in the ready queue (turnaroundTime - burstTime)
};

#endif // End of include guard
