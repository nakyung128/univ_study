#include <iostream>
using namespace std;

const int SIZE = 15;
int A[SIZE] = { 10, 4, 7, 1, -2, 12, 28, 66, 9, 3, 5, 7, 6, 21, 11 };


void print_data()
{
	for (int i = 0; i < SIZE; i++)
		cout << " " << A[i] << " ";
	cout << endl;
}

void quick_sort(int L, int R)
{
	int i, j, temp, t;

	if (R > L)
	{
		temp = A[L];
		i = L;
		j = R + 1;
		do
		{
			do { i = i + 1; } while (A[i] < temp);
			do { j = j - 1; } while (j >= L && A[j] > temp);
			if (i < j)
			{
				// swap A[i] and A[j] 
				t = A[i];
				A[i] = A[j];
				A[j] = t;
			}
		} while (j > i);

		// swap A[L] and A[j] 
		t = A[j];
		A[j] = A[L];
		A[L] = t;
		quick_sort(L, j - 1);
		quick_sort(j + 1, R);
	} 
}

void main()
{
	cout << "Input Data : ";
	print_data();

	/* sort the elements of array L[] in ascending order */
	quick_sort(0, SIZE - 1);

	cout << "\n\nSorted Data : ";
	print_data();

}
