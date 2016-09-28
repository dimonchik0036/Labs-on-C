//LABA 0-num-sys
//by Dimonchik0036

#define _CRT_SECURE_NO_WARNINGS

#define SIZE_ARRAY 20
#define SIZE_AFTER 12

#include <stdlib.h>
#include <stdio.h>

typedef
unsigned long long int64;

//Проверяет реальность данных 2ой строки, а так же считает длину целой и дробной части
short int check(int b1, char *arr, const int size, int &sizeInt, int &sizeReal);

//Возвращает цифру вместо символа
int short transOfLetters(char &countI);

//Возвращает символ вместо цифры
char transInLetters(int countI);

int main()
{
	//Исходная и конечная СС
	int b1, b2;

	//Ввод исходной и требуемой СС
	scanf( "%d%d", &b1, &b2);

	if ((b1 < 2) || (b1 > 16) || (b2 <2) || (b2 > 16))
	{
		printf("bad input");

		return 0;
	};
	
	char countArray[SIZE_ARRAY]; //Массив с полученной строкой
	int sizeInt = 0; //Количество символов в целой части
	int sizeReal = -1; //Количество символов после запятой (с поправкой на \0 символ)

	//Ввод массива
	scanf( "%s", countArray);

	//Проверка массива и получение его размеров
	if (check(b1, countArray, SIZE_ARRAY, sizeInt, sizeReal))
	{
		printf("bad input");

		return 0;
	};

	int64 intFraction = 0; //Целая часть числа
	int64 realFraction = 0; //Дробная часть

	int i;
	int64 b1_new = 1;

	for (i = sizeInt - 1; i >= 0; i--)
	{
		if ((transOfLetters(countArray[i]) >= b1) || (transOfLetters(countArray[i]) < 0))
		{
			printf("bad input");

			return 0;
		}

		intFraction += transOfLetters(countArray[i])*b1_new;
		b1_new*=b1;
	}

	//Если существует дробная часть, то
	if (sizeReal > 0)
	{
		b1_new = 1;
		for (i = (sizeReal + sizeInt); i > (sizeInt); i--)
		{
			if ((transOfLetters(countArray[i]) >= b1) || (transOfLetters(countArray[i]) < 0))
			{
				printf("bad input");

				return 0;
			}

			realFraction += transOfLetters(countArray[i])*b1_new;
			b1_new *= b1;
		}
	}

	//Частное рассмотрение случая, когда целой части нет
	if (intFraction == 0)
	{
		printf("0");
	}

	int n = 0; //Счётчик степени
	int64 b2_new = 1; //b2 в степени

	while (intFraction / b2_new > 0)
	{
		++n;

		b2_new *= b2;
	}

	--n; //Выравнивание значения

	int count; //Контейнер для значения

	//Подсчёт и вывод конечного числа в требуемой СС
	while (n >= 0)
	{
		b2_new /= b2;
		count = intFraction / b2_new;

		printf( "%c", transInLetters(count));

		intFraction -= b2_new*count;

		--n;
	}
	//Дробная часть числа, если таковая имелась
	if (realFraction)
	{
		
		//Вывод разделительной точки
		printf( ".");

		//Частный случай, когда исходная СС == требуемой
		if (b1 == b2)
		{
			for (i = sizeInt + 1; i < (sizeInt + sizeReal + 1); i++)
				printf( "%c", transInLetters(transOfLetters(countArray[i])));

			return 0;
		};

		int64 b1_maxStep = 1;

		for (int i = 0; i < sizeReal; i++)
			b1_maxStep *= b1;

		n = 0; //Служит счётчиком для ограничения 12ти знаков

		while ((realFraction != 0) && (n < SIZE_AFTER))
		{
			n++;

			printf("%c", transInLetters(realFraction * b2 / b1_maxStep));

			realFraction = realFraction * b2 % b1_maxStep;
		}
	}

	return 0;
}

short int check(int b1, char *arr, const int size, int &sizeInt, int &sizeReal)
{
	int flag = 1;
	int i = 0;

	while (arr[i] != '\0')
	{
		if (((arr[i] < '0') || (arr[i] > '9')) &&
		    ((arr[i] < 'A') || ((arr[i] > 'F'))) &&
		    ((arr[i] < 'a') || ((arr[i] > 'f'))))
		{
			if (((arr[i] == '.') || (arr[i] == ',')) && flag)
				flag = 0;
			else
				return 1;
		}

		if (flag)
			++sizeInt;
		else
			++sizeReal;

		if ((sizeInt > size - 2) || (sizeInt + sizeReal > size - 1))
			return 1;

		++i;
	}

	if (arr[0] == '.')
		return 1;


	if (arr[sizeInt + 1] == '\0')
		return 1;

	return 0;
}

int short transOfLetters(char &countI)
{
	if (countI >= 'a' && countI <= 'z')
		countI += 'A' - 'a';

	return (countI >= 'A' && countI <= 'Z') ? (10 + countI - 'A') : (countI - '0');
}

char transInLetters(int countI)
{
	return (countI >= 0 && countI <= 9) ? ('0' + countI) : ('A' - 10 + countI);
}
