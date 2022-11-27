#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <omp.h>
#include <windows.h>
using namespace std;



int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	int n;
	int N;
	int* C;
	int b;
	bool fail = false;
	do {
		fail = false;
		cout << "Введите размер массива = ";
		cin >> N;
		if (cin.fail() || (N <= 0)) {
			cout << "Ошибка ввода, повторите ввод" << endl;
			fail = true;
		}
		cin.clear();
		cin.ignore();
	} while (fail);
	do {
		fail = false;
		cout << "Введите кол-во потоков = ";
		cin >> n;
		if (cin.fail() || n <= 0) {
			cout << "Ошибка ввода, повторите ввод" << endl;
			fail = true;
		}
		cin.clear();
		cin.ignore();
	} while (fail);
	do {
		fail = false;
		cout << "Введите число b = ";
		cin >> b;
		if (cin.fail() || (b <= 0)) {
			cout << "Ошибка ввода, повторите ввод" << endl;
			fail = true;
		}
		cin.clear();
		cin.ignore();
	} while (fail);
	C = new int[N];
	for (int i = 0; i < N; i++) {
		C[i] = 1 + rand() % 10000000;
	}
	double time = omp_get_wtime();
	omp_set_dynamic(false);
	omp_set_num_threads(n);

	long unsigned int count = 0;
	long unsigned int count1 = 0;

#pragma omp parallel firstprivate(count1) shared(count)
	{
		count1 = 0;

#pragma omp for
		for (int i = 0; i < N; i++)
		{
			if (C[i] == b)
			{
				count1 += 1;
			}
		}
#pragma omp critical
		{
			count += count1;

		}
	}
	cout << "Количество элементов b = " << count << "\n";
	time = omp_get_wtime() - time;
	cout << "Время вычислений = " << time << "\n";

	time = omp_get_wtime();

	count = 0;

#pragma omp parallel for reduction (+: count)  

	for (int i = 0; i < N; i++)
	{
		if (C[i] == b)
		{
			count += 1;
		}
	}

	time = omp_get_wtime() - time;
	cout << "Количество элементов b через редукцию = " << count << "\n";
	cout << "Время вычислений = " << time << "\n";

	time = omp_get_wtime();

	count = 0;
	for (int i = 0; i < N; i++)
	{
		if (C[i] == b)
		{
			count += 1;
		}
	}

	time = omp_get_wtime() - time;
	cout << "Количество элементов b без потоков = " << count << "\n";
	cout << "Время вычислений = " << time << "\n";

	delete[]C;
	system("pause");
	return 0;
}
