#include <stdio.h>
#include <stdlib.h>
#define size 10

typedef struct stack
{
	int val;
	struct stack *next;
} stack;

/*stack e eleman gönder*/
int push(stack **base,int key)
{
	if(*base == NULL)
	{
		*base = (stack *)malloc(sizeof(stack));
		(*base)->next = NULL,
		(*base)->val = key;
	}
	else
	{
		stack *ptr = (*base);
		//son elemana git
		while (ptr->next != NULL)
			ptr = ptr->next;
		
		ptr->next = (stack *)malloc(sizeof(stack));
		ptr = ptr->next;
		ptr->next = NULL,
		ptr->val = key;
		
	}
	
}

/*stackden eleman çek*/
int pop(stack **base, int *retval)
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

	stack *ptr = (*base);
	//son elemana git
	while (ptr->next != NULL)
		ptr = ptr->next;
	//değeri al
	*retval = ptr->val;
	//sondan önceki elemana git ve sonu sil
	stack *temp = *base;
	while (temp->next != ptr)
		temp = temp->next;
	free(ptr);
	temp->next = NULL;
	return 0;
}

int main()
{
	int number[size] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};

	stack *base = NULL;

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
			printf("stack boş\n");
			break;
		}
	}
	printf("\n");
}