#include <stdio.h>
#include <stdlib.h>
#define size 6
#define maxCost 999

void createMatrix(int ***matrix, int input[size][size], int **d, int **p)
{
	*matrix = (int **)malloc(size * sizeof(int *));
	*d = (int *)malloc(size * sizeof(int *));
	*p = (int *)malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++)
		(*matrix)[i] = (int *)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			(*matrix)[i][j] = input[i][j];
}

int shortEdge(int ***matrix, int ***E)
{
	int length = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if ((*matrix)[i][j] != 0)
				length++;
	length = length / 2;

	(*E) = (int **)malloc(length * sizeof(int *));

	for (int i = 0; i < length; i++)
		(*E)[i] = (int *)malloc(3 * sizeof(int));

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			(*E)[i][j] = 0;
		}
		//printf("%d-%d-%d",E[i][0],E[i][1],E[i][2]);
	}
	printf("siralanmamis E degerleri\n");
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((*matrix)[i][j] != 0 && j > i)
			{
				(*E)[k][0] = i;
				(*E)[k][1] = j;
				(*E)[k][2] = (*matrix)[i][j];
				printf("-%d-%d-%d\n", (*E)[k][0], (*E)[k][1], (*E)[k][2]);
				k++;
			}
		}
	}
	//siralama
	int temp[3];
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			if ((*E)[j][2] > (*E)[j + 1][2])
			{
				temp[0] = (*E)[j][0];
				temp[1] = (*E)[j][1];
				temp[2] = (*E)[j][2];
				(*E)[j][0] = (*E)[j + 1][0];
				(*E)[j][1] = (*E)[j + 1][1];
				(*E)[j][2] = (*E)[j + 1][2];
				(*E)[j + 1][0] = temp[0];
				(*E)[j + 1][1] = temp[1];
				(*E)[j + 1][2] = temp[2];
			}
		}
	}
	printf("siralanmis E degerleri\n");
	for (int i = 0; i < length; i++)
	{
		printf("-%d-%d-%d\n", (*E)[i][0], (*E)[i][1], (*E)[i][2]);
	}

	return length;
}

void initialize(int v,int **d, int **p)
{
	for (int i = 0; i < size; i++)
	{
		(*d)[i] = maxCost;
		(*p)[i] = -1;
	}
	(*d)[v] = 0;
}

void relax(int u, int v,int **d, int **p, int ***matrix)
{
	if ((*d)[v] > (*d)[u] + (*matrix)[u][v])
	{
		(*d)[v] = (*d)[u] + (*matrix)[u][v];
		(*p)[v] = u;
	}
}

int bellmanford(int v, int **d, int **p, int ***matrix, int ***E)
{
	initialize(v,&(*d), &(*p));

	int length = shortEdge(&(*matrix),&(*E));
	for (int j = 0; j < size; j++)
		for (int i = 0; i < length; i++)
			relax((*E)[i][0], (*E)[i][1], &(*d), &(*p), &(*matrix));

	for (int i = 0; i < length; i++)
		if ((*d)[(*E)[i][0]] > (*d)[(*E)[i][1]] + (*E)[i][2])
			return -1;

	return 0;
}

int main()
{							 //a  b  c  d  e  f
	int input[size][size] = {{0, 9, 0, 0, 2, 0},//a
							 {9, 0, 7, 0, 1, 0},//b
							 {0, 7, 0, 9, 0, 0},//c
							 {0, 0, 9, 0, 8, 4},//d
							 {2, 1, 0, 8, 0, 1},//e
							 {0, 0, 0, 4, 1, 0}};//f

	int **matrix; //matrisin kendisi
	int *d;		  //maliyet dizisi
	int *p;		  //atasini tutan dizi
	int **E;
	createMatrix(&matrix, input, &d, &p);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}

	//başlangıç durumu
	int v = 0;
	bellmanford(v, &d, &p, &matrix, &E);
	printf("erişilebilen düğümler:\n");
	for (int i = 0; i < size; i++)
		printf("dugum = %d - atasi = %d - bedeli = %d\n", i, p[i], d[i]);

	return 0;
}