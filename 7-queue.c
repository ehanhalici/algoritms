#include <stdio.h>
#include <stdlib.h>
#define size 10

typedef struct queue
{
	int val;
	struct queue *next;
} queue;

/*queue e eleman gönder*/
int push(queue **base,int key)
{
	if(*base == NULL)
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
	if((*base)->next == NULL)
	{
		*retval = (*base)->val;
		free(*base);
		(*base) = NULL;
		return 0;
	}

	queue *ptr = (*base);
	//tabanı ileri al
	(*base) =(*base)->next;
	//değeri al
	*retval = ptr->val;
	free(ptr);
	return 0;
}

int main()
{
	int number[size] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};

	queue *base = NULL;

	//Eleman ekle
	for (size_t i = 0; i < size; i++)
	{
		push(&base, number[i]);
	}
	int val = 0;
	for (size_t i = 0; i < size; i++)
	{
		if(!pop(&base,&val))
			printf("%d - ",val);
		else
		{
			printf("queue boş\n");
			break;
		}
	}
	printf("\n");
}