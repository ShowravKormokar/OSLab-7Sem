#include <iostream>
using namespace std;

int p1(int a)
{
	return a += 1;
}

int p2(int a)
{
	return a += 1;
}

int main()
{
	// Initial value of a
	int a = 10;

	int temp1 = a; // Step1: Process 1 read a=10
	int temp2 = a; // Step2: Process 2 read a=10

	// Step3: Process 1 increase value 1
	a = p1(temp1); // Step4: Process 1 set updated value of a
	cout << "P1 is: " << a << endl;

	// Step5: Process 2 increase value 1
	a = p2(temp2); // Step6: Process 2 set updated value of a
	cout << "P2 is: " << a << endl;

	cout << "Updated value of a: " << a << "\t(Race Condition)" << endl;
	cout << "Expected value of a: 12" << endl;

	return 0;
}