#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h> /* prototype exit() */
#include <string.h>
#include <locale.h>

#define MAX_SIZE 100
int move_to_front(char *str, char c)
{
	char *q, *p;
	int shift = 0;
	p = (char *)malloc(strlen(str) + 1);
	strcpy(p, str);//копируем строки
	q = strchr(p, c); //returns pointer to location of char c in string str
	shift = q - p;      // no of characters from 0 to position of c in str
	strncpy(str + 1, p, shift);//перезаписываем алфавит
	str[0] = c;
	free(p);
	//  printf("\n%s\n",str);
	return shift;
}

void decode(int* pass, int size, char *sym)
{
	int i, index;
	char c;
	char table[] = "abcdefghijklmnopqrstuvwxyz";
	for (i = 0; i < size; i++)
	{
		c = table[pass[i]];
		index = move_to_front(table, c);
		if (pass[i] != index) printf("there is an error");
		sym[i] = c;
	}
	sym[size] = '\0';
}




void main() {
	setlocale(LC_ALL, "Rus");
	int i = 0, j = 0;
	//	char base[10][100];
	char base1[10][100];
	FILE *fo, *fi, *fiout, *fa, *farch;
	//	int cnt = 0;
	char chIn[20], chOut[20], chArch[20];
	int pre = EOF;
	int *pass1;
	// переходим в консоли на русский язык
	system("cls");       // очищаем окно консоли
						 //loop1:
	printf("Файлы для работы программы расположены в папке D:\\MTF\: "); // выводим сообщение
	char start[28] = "D:\\\MTF/";
	char start1[28] = "D:\\\MTF/";
	char start2[28] = "D:\\\MTF/";
	int flag = 0;
	printf("Введите имя файла для извлечения из архива: "); // выводим сообщение
	scanf("%s", &chArch);     // вводим значения переменной y
	farch = fopen("E:\\MTF/archiv.txt", "r");
	// Переменная, в которую поочередно будут помещаться считываемые строки
	char str[100];
	char str1[100];
	//Указатель, в который будет помещен адрес массива, в который считана строка, или NULL если достигнут конец файла или произошла ошибка
	char *estr, *estr1;
	char *istr, *istr1;
	char *strstep;
	int P;
	char *sym;
	while (1)
	{
		// Чтение одной строки  из файла
		estr = fgets(str, sizeof(str), farch);//считывваем строку

		//Проверка на конец файла или ошибку чтения
		if (estr == NULL)
		{
			// Проверяем, что именно произошло: кончился файл  или это ошибка чтения
			if (feof(farch) != 0)
			{
				//Если файл закончился, выводим сообщение о завершении //чтения и выходим из бесконечного цикла
				printf("\nЧтение файла закончено\n");
				break;
			}
			else
			{
				//Если при чтении произошла ошибка, выводим сообщение //об ошибке и выходим из бесконечного цикла
				printf("\nОшибка чтения из файла\n");
				break;
			}
		}
		//Если файл не закончился, и не было ошибки чтения //выводим считанную строку  на экран
		if ((strstr(str, chArch) != NULL) && (strstr(str, "START") != NULL)) {
			flag++;
			printf("     %s", str);
		}
		if ((strstr(str, chArch) != NULL) && (strstr(str, "END") != NULL)) {
			flag = 0;
			printf("     %s", str);
		}
		if ((strstr(str, chArch) == NULL) && (flag > 0)) {
			P = 0;
			strncpy(str1, str, 100);
			istr = strtok(str, " ");

			while (istr != NULL)
			{


				P++;
				// Выделение очередной части строки
				istr = strtok(NULL, " ");

				// 
			}
			pass1 = (int *)malloc((P - 2) * sizeof(int));

			istr1 = strtok(str1, " ");
			//	printf(" str-->    %s", str);
			i = 0;
			while (i < P - 1)
			{
				pass1[i] = atoi(istr1);//преобразуем строку в число
				//	printf(" pass1-->    %d\n", pass1[i]);
				i++;
				istr1 = strtok(NULL, " ");//выделение очередной части строки

			}
			i = 0;
			P = P - 1;
			//	printf("P=%d ", P);
			//	printf("%d ", pass1[P]);
			char *sym = malloc(sizeof(char)*(P));
			decode(pass1, P, sym);
			printf("%s\n", sym);



		}
	}
	system("pause");
}