#include <stdio.h>
#include <stdlib.h>
#define size 6

void createMatrix(int ***matrix, int input[size][size], int **damage, int **color, int **father, int **f)
{
	*matrix = (int **)malloc(size * sizeof(int *));
	*damage = (int *)malloc(size * sizeof(int *));
	*color = (int *)malloc(size * sizeof(int *));
	*father = (int *)malloc(size * sizeof(int *));
	*f = (int *)malloc(size * sizeof(int *));

	for (int i = 0; i < size; i++)
		(*matrix)[i] = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			(*matrix)[i][j] = input[i][j];
}

void dfsVisit(int u, int ***matrix, int **damage, int **color, int **father, int **f, int *time)
{
	//ziyaret edilmis ama islenmemis
	(*color)[u] = 1;
	//ilk islenme zamani ata sonra zamani arttir
	(*damage)[u] = ++(*time);

	//tum komsular icin
	for (int i = 0; i < size; i++)
	{
		//komsusu varsa, olmayadabilir
		if ((*matrix)[u][i] != 0)
		{
			if ((*color)[i] == 0)
			{
				(*father)[i] = u;
				dfsVisit(i, &(*matrix), &(*damage), &(*color), &(*father), &(*f), &(*time));
			}
		}
	}
	//tam islenmis
	(*color)[u] = 2;
	//tam islenme zamani
	(*f)[u] = ++(*time);
}

void dfs(int v, int ***matrix, int **damage, int **color, int **father, int **f)
{
	//butun dugumler icin
	for (int i = 0; i < size; i++)
	{
		(*color)[i] = 0;
		(*father)[i] = -1;
	}

	int time = 0;
	//butun dugumler icin
	for (int i = 0; i < size; i++)
	{
		//komsusu ziyaret edilmemisse ziyaret et
		if (color[i] == 0)
			dfsVisit(i, &(*matrix), &(*damage), &(*color), &(*father), &(*f), &time);
	}
}


int main()
{
	int input[size][size] = {{0, 9, 0, 0, 2, 0},
							 {9, 0, 7, 0, 1, 0},
							 {0, 7, 0, 9, 0, 0},
							 {0, 0, 9, 0, 8, 4},
							 {2, 1, 0, 8, 0, 1},
							 {0, 0, 0, 4, 1, 0}};

	int **matrix; //matrisin kendisi
	int *damage;  //maliyet dizisi
	int *color;	  //ulasilma dizisi
	int *father;  //atasini tutan dizi
	int *f;		  //düğüm işleme zanamanı
	createMatrix(&matrix, input, &damage, &color, &father, &f);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}

	//başlangıç durumu
	int v = 0;
	dfs(v, &matrix, &damage, &color, &father, &f);
	//
	printf("erişilebilen düğümler:\n");
	for (int i = 0; i < size; i++)
	{
		if (color[i] == 2)
			printf("dugum = %d - atasi = %d - ilk bedeli = %d - son bedeli = %d \n", i, father[i], damage[i], f[i]);
		else
			printf("DFS tamamlanamadı ulaşılamayan düğümler var");
	}

	return 0;
}