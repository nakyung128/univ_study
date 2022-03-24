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

void merge(int A[], int L, int R, int m)
{
	int i, j, k;
	int B[20];

	for (i = L; i <= m; i++) B[i] = A[i];
	for (j = m; j < R; j++) B[R + m - j] = A[j + 1];

	i = L; j = R;
	for (k = L; k <= R; k++)
	{
		A[k] = (B[i] < B[j] ? B[i++] : B[j--]);
	}
}

void merge_sort(int A[], int L, int R)
{
	int m;

	if (R > L)
	{
		m = (R + L) / 2;
		merge_sort(A, L, m);
		merge_sort(A, m + 1, R);
		merge(A, L, R, m);
	}
}

void main()
{
	cout << "Input Data : ";
	print_data();

	/* sort the elements of array L[] in ascending order */
	merge_sort(A, 0, SIZE - 1);

	cout << "\n\nSorted Data : ";
	print_data();

}
