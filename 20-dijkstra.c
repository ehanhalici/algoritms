#include <stdio.h>
#include <stdlib.h>
#define size 6
#define maxCost 999

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

/*queueden en az maliyetli elemanı çıkart*/
int pop(queue **base, int **d, int *retval)
{
	int cost = maxCost;

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
	queue *temp = ptr;
	//en az maliyetliyi bul
	while (ptr->next != NULL)
	{
		if ((*d)[ptr->val] < cost)
		{
			cost = (*d)[ptr->val];
			temp = ptr;
		}
		ptr = ptr->next;
	}
	//bulunan root ise
	if (temp == (*base))
	{
		(*base) = (*base)->next;
		*retval = temp->val;
		free(temp);
		return 0;
	}
	//bulunan sonuncu ise
	else if (temp->next == NULL)
	{
		*retval = temp->val;
		temp = NULL;
		free(temp);
		return 0;
	}
	//arada biyerde ise
	else
	{
		ptr = (*base);
		while (ptr->next != temp)
			ptr = ptr->next;

		ptr->next = temp->next;
		*retval = temp->val;
		free(temp);
		return 0;
	}
}

void createMatrix(int ***matrix, int input[size][size], int **d, int **father)
{
	*matrix = (int **)malloc(size * sizeof(int *));
	*d = (int *)malloc(size * sizeof(int *));
	*father = (int *)malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++)
		(*matrix)[i] = (int *)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			(*matrix)[i][j] = input[i][j];
}

int find(int v, queue **base)
{
	queue *ptr = *base;
	if (ptr == NULL)
		return -1;

	if (ptr->next != NULL)
	{
		while (ptr->next != NULL)
		{
			if (ptr->val == v)
				return 1;

			else
				ptr = ptr->next;
		}
	}
	else
	{
		if (ptr->val == v)
			return 1;
	}
	return 0;
}

void initialize(int v, int **d, int **father)
{
	for (int i = 0; i < size; i++)
	{
		(*d)[i] = 999;
		(*father)[i] = -1;
	}

	(*d)[v] = 0;
}

void relax(int u, int v,int ***matrix, int **d, int **father)
{
	if ((*d)[v] > (*d)[u] + (*matrix)[u][v])
	{
		(*d)[v] = (*d)[u] + (*matrix)[u][v];
		(*father)[v] = u;
	}
}

void dijkstra(int v, int ***matrix, int **d, int **father, queue **base)
{
	initialize(v,&(*d),&(*father));

	for (int i = 0; i < size; i++)
		push(&(*base),i);

	while ((*base) != NULL)
	{
		int u;
		pop(&(*base),&(*d),&u);
		for (int i = 0; i < size; i++) //u nun tummm
			if ((*matrix)[u][i] != 0) //komusulari icin
				relax(u, i,&(*matrix),&(*d),&(*father));
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

	int **matrix;		//matrisin kendisi
	int *d;				//maliyet dizisi
	int *father;		//atasini tutan dizi
	queue *base = NULL; // kuyruk yapısı
	createMatrix(&matrix, input, &d, &father);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}

	//başlangıç durumu
	int v = 0;
	dijkstra(v, &matrix, &d, &father, &base);

	printf("erişilebilen düğümler:\n");
	for (int i = 0; i < size; i++)
		printf("dugum = %d - atasi = %d - bedeli = %d\n", i, father[i], d[i]);

	return 0;
}
