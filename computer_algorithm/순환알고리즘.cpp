#include<iostream>
using namespace std;

// ���丮��
int factorial(int n) // n! = n * (n - 1)!, 1! = 1, 0! = 1
{
	if (n == 0) return (1);
	else if (n == 1) return (1);
	else return (n * factorial(n - 1));
}

//�Ǻ���ġ ����
int Fibonacci(int n) // F(n) = F(n - 2) + F(n - 1), n > 1, F(0) = F(1) = 1;
{
	if (n == 0) return (1);
	else if (n == 1) return(1);
	else return(Fibonacci(n - 2) + Fibonacci(n - 1));
}

void main() {
	int n;
	cout << "���ڸ� �Է��ϼ���: ";
	cin >> n;

	cout << n << "! = " << factorial(n) << endl;
}