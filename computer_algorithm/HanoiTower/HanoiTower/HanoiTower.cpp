#include <iostream> 
using namespace std;

int cnt = 0; // �̵� Ƚ���� �̿�.

void Hanoi(int n, char from, char temp, char to)
// n : ���ݰ���, from : ���� ��ġ, temp : �ӽ� ���, to :������
{
	if (n == 1)
	{
		cout << "���� 1����" << from << "���� " << to << "�� �̵��Ѵ�.\n";
		cnt++;
	}
	else
	{
		Hanoi(n - 1, from, to, temp);
		cout << "���� " << n << "���� " << from << "���� " << to << "�� �̵��Ѵ�.\n";
		Hanoi(n - 1, temp, from, to);
		cnt++;
	}
}


void main()
{
	int n; //������ ��

	cout << "������ ������ �Է��ϼ��� : ";
	cin >> n;

	Hanoi(n, 'A', 'B', 'C');    // n���� ������ 'A'���� 'C'�� �̵�

	cout << "��ü ���� �̵� ��(���ݼ� : " << n << ") = " << cnt << endl;
}