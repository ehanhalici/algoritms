#include <stdio.h>
#include <stdlib.h>
#define size 6

typedef struct queue
{
	int val;
	struct queue *next;
} queue;

/*queue e eleman gönder*/
int push(queue **base, int key)
{
	if (*base == NULL)
	{
		*base = (queue *)malloc(sizeof(queue));
		(*base)->next = NULL,
		(*base)->val = key;
	}
	else
	{
		queue *ptr = (*base);
		//son elemana git
		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = (queue *)malloc(sizeof(queue));
		ptr = ptr->next;
		ptr->next = NULL,
		ptr->val = key;
	}
}

/*queueden eleman çek*/
int pop(queue **base, int *retval)
{
	if (*base == NULL)
		return -1;
	if ((*base)->next == NULL)
	{
		*retval = (*base)->val;
		free(*base);
		(*base) = NULL;
		return 0;
	}

	queue *ptr = (*base);
	//tabanı ileri al
	(*base) = (*base)->next;
	//değeri al
	*retval = ptr->val;
	free(ptr);
	return 0;
}

void createMatrix(int ***matrix, int input[size][size], int **damage, int **color, int **father)
{
	*matrix = (int **)malloc(size * sizeof(int *));
	*damage = (int *)malloc(size * sizeof(int *));
	*color = (int *)malloc(size * sizeof(int *));
	*father = (int *)malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++)
		(*matrix)[i] = (int *)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			(*matrix)[i][j] = input[i][j];
}

void bfs(int v, int ***matrix, int **damage, int **color, int **father, queue **base)
{
	//her bir düğüm için başta şu işlemleri yap
	for (int i = 0; i < size; i++)
	{
		(*damage)[i] = 99999; //maliyeti sonsuz la
		(*color)[i] = 0;	  //ziyaret edilmedi yap
		(*father)[i] = -1;	  //atasi yok
	}
	//baslangic dugumu icin gerekli hazirlikalr
	(*color)[v] = 1;
	(*damage)[v] = 0;
	(*father)[v] = -1;

	push(&(*base), v);

	while ((*base) != NULL)
	{
		int x = 0;
		int u;
		pop(&(*base), &u);

		for (int i = 0; i < size; i++)
		{
			// tüm komşuları için, ziyaret edilmemişlerse
			if ((*matrix)[u][i] != 0 && (*color)[i] == 0)
			{
				(*color)[i] = 1; //rengini gri yap
				(*damage)[i] = (*damage)[u] + 1;
				(*father)[i] = u;
				push(&(*base), i);
			}
		}
		(*color)[u] = 2;
		printf("%d - ", u);
	}
	printf("\n");
}

int main()
{
	int input[size][size] = {{0, 9, 0, 0, 2, 0},
							 {9, 0, 7, 0, 1, 0},
							 {0, 7, 0, 9, 0, 0},
							 {0, 0, 9, 0, 8, 4},
							 {2, 1, 0, 8, 0, 1},
							 {0, 0, 0, 4, 1, 0}};

	int **matrix;		//matrisin kendisi
	int *damage;		//maliyet dizisi
	int *color;			//ulasilma dizisi
	int *father;		//atasini tutan dizi
	queue *base = NULL; // kuyruk yapısı
	createMatrix(&matrix, input, &damage, &color, &father);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}

	//başlangıç durumu
	int v = 0;
	bfs(v, &matrix, &damage, &color, &father, &base);
	//
	printf("erişilebilen düğümler:\n");
	for (int i = 0; i < size; i++)
	{
		if (color[i] == 2)
			printf("dugum = %d - atasi = %d - bedeli = %d\n", i, father[i], damage[i]);
		else 
			printf("Bfs tamamlanamadı ulaşılamayan düğümler var");
	}

	return 0;
}
