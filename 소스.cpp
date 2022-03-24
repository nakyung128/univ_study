#include <iostream>
using namespace std;

#define SWAP(x, y, t) (t=x, x=y, y=t)

double L[15] = { 10, 4, 0, 1, -2, 12, 28, 66, 9, 3, 5, 7, 6, 21, 11 };

void print_data(double L[], int n)
{
	for (int i = 0; i < n; i++)
		cout << " " << L[i];
	cout << endl;
}

void Max_heap(double L[], int root, int n)
{
	double root_data = L[root];
	int child = root * 2 + 1;
	while (child <= n - 1)
	{
		if (child < (n - 1) && L[child] < L[child + 1])
			child++;
		if (root_data > L[child]) break;
		else {
			L[(child - 1) / 2] = L[child];
			child = child * 2 + 1;
		}
	}
	L[(child - 1) / 2] = root_data;
}

void HeapSort(double L[], int n)
{
	int i, temp;

	// 최대 히프 구조 생성
	for (i = (n - 2) / 2; i >= 0; i--)
		Max_heap(L, i, n);

	// 실제 정렬
	// 제일 큰 수(0번째 원소)를 마지막(n-1번째)으로 옮기고 나머지를 다시 heap으로
	for (i = n - 1; i >= 0; i--)
	{
		//두 원소 L[0],L[i+1] 교환
		SWAP(L[0], L[i], temp);
		Max_heap(L, 0, i);
	}
}

void main()
{
	// 처음 상태를 보여줌
	cout << "Input Data : ";
	print_data(L, 15);

	/* sort the elements of array L[] in ascending order */
	HeapSort(L, 15);

	// 정렬된 결과를 보여줌
	cout << "\nSorted Data : ";
	print_data(L, 15);

}