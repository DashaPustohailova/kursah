#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#define NO 0
#define YES 1
#define MAX_SIZE 100

int move_to_front(char *str, char c)
{
	char *q, *p;
	int shift = 0;
	p = (char *)malloc(strlen(str) + 1);
	strcpy(p, str);
	q = strchr(p, c);
	shift = q - p;
	strncpy(str + 1, p, shift);
	str[0] = c;
	free(p);
	return shift;
}


void name()
{
	char word[20], line[100];
	char *ptr, *farch;
	int i = 0;
	farch = fopen("archiv.txt", "r");
	while (!feof(farch))
	{
		ptr = fgets(line, sizeof(line), farch);
		word[0] = '\0';
		if (strstr(line, "*START") != NULL)
		{
			while (*ptr != '*')
			{
				word[i++] = *ptr++;
			}
			word[i] = '\0';
			i = 0;
			printf("%s\n", word);
		}
	}
	getchar();
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


void encode(char *sym, int size, int *pass)
{
	int i = 0;
	char c;
	char table[] = "abcdefghijklmnopqrstuvwxyz";
	for (i = 0; i < size; i++)
	{
		c = sym[i];
		pass[i] = move_to_front(table, c);
	}
}


int check(char *sym, int size, int *pass)
{
	int *pass2 = malloc(sizeof(int)*size);
	char *sym2 = malloc(sizeof(char)*size);
	int i, val = 1;

	encode(sym, size, pass2);
	i = 0;
	while (i < size && pass[i] == pass2[i])i++;
	if (i != size)val = 0;

	decode(pass, size, sym2);
	if (strcmp(sym, sym2) != 0) val = 0;

	free(pass2);

	return val;
}

void main()
{
	int exit = NO;
	int i = 0, j = 0;
	char base[10][100];
	char base1[10][100];
	FILE *fo, *fiout, *fa, *farch;
	int cnt = 0;
	char chIn[20], chOut[20], chArch[20];
	int pre = EOF;
	int *pass1;
	int s;
	int flag = 0;

	do
	{
		system("cls");
		printf("1.File coding\n2.File decoding\n3.Exit\n");
		scanf("%i", &s);
		switch (s)
		{
		case 1:
			system("cls");
		loop1:

			printf("Enter the file name to encode:");
			scanf("%s", &chIn);

			fo = fopen(chIn, "r");
			if (fo == NULL) {
				printf("Error\n");
				goto loop1;
			}

			while (!feof(fo)) {
				fscanf(fo, "%s", base[i]);
				i++;
			}
			cnt = i;

			int pass[MAX_SIZE] = { 0 };
			int len;
			for (i = 0; i < cnt; i++)
			{
				len = strlen(base[i]);
				encode(base[i], len, pass);


				printf("%s : [", base[i]);
				for (j = 0; j < len; j++)
					printf("%d ", pass[j]);

				printf("]\n");

				if (check(base[i], len, pass))
					printf("Correct :)\n");
				else
					printf("Incorrect :(\n");
			}

			int choice;
		loop4:

			printf("Select an action:\n 1 - add to archive\n 2 - complete work:\n");
			scanf("%i", &choice);

			switch (choice)
			{
			case 1:
				fiout = fopen(chIn, "r");

				fa = fopen("archiv.txt", "a");
				fprintf(fa, chIn); fprintf(fa, "*START");
				fprintf(fa, "\n");
				int i1 = 0;
				int cnt1 = 0;
				while (!feof(fiout)) {
					fscanf(fiout, "%s", base1[i1]);
					i1++;
				}
				cnt1 = i1;
				int pass1[MAX_SIZE] = { 0 };
				int len1, j1;
				for (i1 = 0; i1 < cnt1; i1++)
				{
					len1 = strlen(base1[i1]);
					encode(base[i1], len1, pass1);
					for (j1 = 0; j1 < len1; j1++) {
						fprintf(fa, "%d ", pass1[j1]);
					}
					fprintf(fa, "\n");
				}

				fprintf(fa, chIn); fprintf(fa, "*END\n");
				fclose(fa);
				break;

			case 2:

				fclose(fo);
				exit = YES;
				break;
			default:
				printf("Error.\n");
				break;
			}
			break;

		case 2:

			system("cls");
			printf("Name Files in Archiv:\n");
			name();
			printf("\n");
			int *pass2;

			printf("Enter file name: \n");
			scanf("%s", &chArch);
			printf("\n\n");

			farch = fopen("archiv.txt", "r");
			char str_[100];
			char str1_[100];
			char *estr, *estr1;
			char *istr, *istr1;
			char *strstep;
			int P;
			int ok = NO;
			char *sym;

			while (1)
			{
				estr = fgets(str_, sizeof(str_), farch);


				if (estr == NULL)
				{

					if (feof(farch) != 0)
					{
						printf("\nFile reading completed\n");
						break;
					}
					else
					{
						printf("\nError\n");
						break;
					}
				}

				if ((strstr(str_, chArch) != NULL) & (strstr(str_, "START") != NULL)) {
					flag++;
					ok = YES;
					printf("     %s", str_);
				}
				if ((strstr(str_, chArch) != NULL) & (strstr(str_, "END") != NULL)) {
					flag = 0;
					printf("     %s\n", str_);
				}


				if ((strstr(str_, chArch) == NULL) & (flag > 0))
				{
					P = 0;
					strncpy(str1_, str_, 100);
					istr = strtok(str_, " ");

					while (istr != NULL)
					{
						P++;
						istr = strtok(NULL, " ");
					}
					pass2 = (int *)malloc((P - 2) * sizeof(int));

					istr1 = strtok(str1_, " ");
					i = 0;
					while (i < P - 1)
					{
						pass2[i] = atoi(istr1);

						i++;
						istr1 = strtok(NULL, " ");

					}
					i = 0;
					P = P - 1;

					char *sym = malloc(sizeof(char)*(P));
					decode(pass2, P, sym);
					printf("%s \n", sym);
				}
			}

			if (ok == NO) printf("  Error. This file does not exist.\n");
			system("pause");
			break;

		case 3:
			exit = YES;
			break;
		default:
			printf("Please, enter 1,2 or 3\n");
			system("pause");
			break;
		}
	} while (exit == NO);
}
