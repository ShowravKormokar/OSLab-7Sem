#include <iostream>
using namespace std;

int main()
{
    // Initial value of a
    int a = 10;

    int p1 = a; // Step1: Process 1 read a=10
    int p2 = a; // Step2: Process 2 read a=10

    p1 += 1; // Step3: Process 1 increase value 1
    a = p1;  // Step4: Process 1 set updated value of a
    cout << "P1 is: " << p1 << endl;

    p2 += 1; // Step5: Process 2 increase value 1
    a = p2;  // Step6: Process 2 set updated value of a
    cout << "P2 is: " << p2 << endl;

    cout << "Updated value of a: " << a << "\t(Race Condition)" << endl;
    cout << "Expected value of a: 12" << endl;

    return 0;
}