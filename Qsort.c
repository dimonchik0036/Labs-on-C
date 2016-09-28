# Labs
 Labs by Dimonchik0036.

//LABA 3-1-qsort
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

//Сортирует массив
void sorting(int* a, int first, int last);

int main()
{
	const int sizeArray = 2000000;
	int n; //Количество чисел в массиве

	scanf("%d", &n);

	static int numberArray[sizeArray]; //Массив чисел
	int i; //Переменная для цикла

	for ( i = 0; i < n; i++)
		scanf("%d", &numberArray[i]); //Ввод данных в массив

	//Сортировка
	sorting(numberArray, 0, n - 1);

	//Вывод массива
	for (i = 0; i < n; i++)
	{
		printf("%d ", numberArray[i]);
	}

	return 0;
}

void sorting(int* arr, int first, int last)
{
	int i = first;
	int j = last;
	int centr = arr[(first + last) / 2]; //Выбор значения для границы сортировки
	

	do 
	{
		while (arr[i] < centr) 
			i++;
		while (centr < arr[j]) 
			j--;

		if (i <= j) 
		{
			if (i < j)
			{
				int keys = arr[i];
				arr[i] = arr[j];
				arr[j] = keys;
			}
			i++;
			j--;
		}
	} while (i <= j);

	//Вызов сортировки правой части
	if (i < last)
		sorting(arr, i, last);

	//Вызов сортировки левой части
	if (first < j)
		sorting(arr, first, j);
}
