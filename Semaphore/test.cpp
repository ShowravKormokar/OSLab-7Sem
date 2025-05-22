#include <bits/stdc++.h>
using namespace std;

int semaphore = 1;
int x = 1;

void wait()
{
    while (semaphore <= 0)
    {
        // wait until the resource becomes available
    }
    semaphore--; // use the semaphore variable
}

void signal()
{
    semaphore++; // release the semaphore variable
}

void critical_section()
{
    cout << "Entering the critical section: " << endl;
    wait();
    cout << "In the critical section: " << endl;

    x++;
    cout << "Current value of x = " << x << endl;

    cout << "Exiting the critical section: " << endl
         << endl;
    signal();
}

int main()
{
    critical_section();
    critical_section();
}