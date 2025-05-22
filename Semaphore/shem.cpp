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
void processA()
{
    wait(); // Acquire semaphore
    cout << "Process A enters critical section.\n";
    sharedCounter = sharedCounter + 1;
    cout << "Shared Counter (A): " << sharedCounter << endl;
    cout << "Process A leaves critical section.\n\n";
    signal(); // Release semaphore
}

// Simulated Process B
void processB()
{
    wait(); // Acquire semaphore
    cout << "Process B enters critical section.\n";
    sharedCounter = sharedCounter + 2;
    cout << "Shared Counter (B): " << sharedCounter << endl;
    cout << "Process B leaves critical section.\n\n";
    signal(); // Release semaphore
}

// Main function to simulate sequence
int main()
{
    // Simulate calling processes alternately
    processA();
    processB();
    processA();
    processB();

    cout << "Final Shared Counter: " << sharedCounter << endl;

    return 0;
}
