#include <iostream>

using namespace std;

// Global shared resource
int sharedCounter = 0;

// Binary semaphore variable (0 = locked, 1 = available)
int semaphore = 1;

// Wait (P) operation
void wait()
{
    while (semaphore <= 0)
    {
        // Busy wait (skip loop iteration until semaphore is free)
    }
    semaphore = semaphore - 1;
}

// Signal (V) operation
void signal()
{
    semaphore = semaphore + 1;
}

// Simulated Process A
void critical_section(int processNum)
{
    wait(); // Acquire semaphore
    cout << "Process " << processNum << " enters critical section.\n";
    sharedCounter = sharedCounter + 1;
    cout << "Shared Counter (" << processNum << "): " << sharedCounter << endl;
    cout << "Process " << processNum << "  leaves critical section.\n\n";
    signal(); // Release semaphore
}

// Main function to simulate sequence
int main()
{
    // Simulate calling processes alternately
    critical_section(1);
    critical_section(2);

    cout << "Final Shared Counter: " << sharedCounter << endl;

    return 0;
}