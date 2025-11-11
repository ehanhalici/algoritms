#include <stdio.h>
#include <stdlib.h>
#define size 9

void createMatrix(int ***matrix, int input[size][size], int **rank, int **p)
{
	*matrix = (int **)malloc(size * sizeof(int *));
	*rank = (int *)malloc(size * sizeof(int *));
	*p = (int *)malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++)
		(*matrix)[i] = (int *)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			(*matrix)[i][j] = input[i][j];
}

void makeset(int v,int **rank,int **p)
{
	(*p)[v] = v;
	(*rank)[v] = 0;
}

int findset(int v,int **rank, int **p)
{
	if (v != (*p)[v])
		(*p)[v] = findset((*p)[v],&(*rank),&(*p));

	return (*p)[v];
}

void link(int x, int y, int **rank, int **p)
{
	if ((*rank)[x] > (*rank)[y])
		(*p)[y] = x;
	else
	{
		(*p)[x] = y;
		if ((*rank)[x] == (*rank)[y])
			(*rank)[y] = (*rank)[y] + 1;
	}
}

void unionn(int x, int y, int **rank, int **p)
{
	link(findset(x,&(*rank),&(*p)), findset(y,&(*rank),&(*p)),&(*rank),&(*p));
}

int shortEdge(int ***matrix,int ***E)
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
				printf("%c-%c-%d\n", (*E)[i][0] + 97, (*E)[i][1] + 97, (*E)[i][2]);
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
		printf("%c-%c-%d\n", (*E)[i][0] + 97, (*E)[i][1] + 97, (*E)[i][2]);
	}

	return length;
}

void kruskal(int v, int **rank, int **p ,int ***matrix, int ***E)
{
	for (int i = 0; i < size; i++)
	{
		makeset(i, &(*rank),&(*p));
	}

	int length = shortEdge(&(*matrix),&(*E));
	printf("algoritma sonucu kullanilan E degerleri\n");
	for (int i = 0; i < length; i++)
	{
		if (findset((*E)[i][0],&(*rank),&(*p)) != findset((*E)[i][1],&(*rank),&(*p)))
		{
			unionn((*E)[i][0], (*E)[i][1],&(*rank),&(*p));
			printf("%c-%c-%d\n", (*E)[i][0] + 97, (*E)[i][1] + 97, (*E)[i][2]);
		}
	}
}

int main()
{							//a   b   c   d   e   f   g   h   i
	int input[size][size] = {{0 , 4 , 0 , 0 , 0 , 0 , 0 , 8 , 0},  //a
							 {4 , 0 , 8 , 0 , 0 , 0 , 0 , 11, 0},  //b
							 {0 , 8 , 0 , 7 , 0 , 4 , 0 , 0 , 2},  //c
							 {0 , 0 , 7 , 0 , 9 , 14, 0 , 0 , 0},  //d
							 {0 , 0 , 0 , 9 , 0 , 10, 0 , 0 , 0},  //e
							 {0 , 0 , 4 , 14, 10, 0 , 2 , 0 , 0},  //f
							 {0 , 0 , 0 , 0 , 0 , 2 , 0 , 1 , 6},  //g
							 {8 , 11, 0 , 0 , 5 , 0 , 1 , 0 , 7},  //h
							 {0 , 0 , 2 , 0 , 5 , 0 , 6 , 7 , 0}}; //i

	int **matrix; //matrisin kendisi
	int *rank;	  //maliyet dizisi
	int *p;		  //atasini tutan dizi
	int **E;
	createMatrix(&matrix, input, &rank, &p);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}

	//başlangıç durumu
	int v = 0;
	kruskal(v,&rank,&p,&matrix,&E);
	return 0;
}