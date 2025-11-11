
#include <stdio.h>
#include <stdlib.h>
#define size 10

typedef struct list
{
	int val;
	struct list *next;
} list;

/*listeye sıralı olarak eleman ekler*/
int add(list **root, int key)
{
	if (*root == NULL)
	{
		*root = (list *)malloc(sizeof(list));
		(*root)->val = key;
		(*root)->next = NULL;
		return 0;
	}
	list *temp = (list *)malloc(sizeof(list));
	temp->val = key;
	temp->next = NULL;

	list *ptr = *root;

	//kaydileceği yeri belirle
	while (ptr != NULL)
	{
		if (ptr->val > temp->val)
			ptr = ptr->next;
		else
			break;
	}

	// sonda ise sona ekle
	if (ptr == NULL)
	{
		//sondan bir önceki elemana git
		ptr = *root;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}

		ptr->next = temp;
		temp = NULL;
	}
	else if (ptr == *root) //başta ise başa ekle
	{
		temp->next = ptr;
		*root = temp;
		temp = NULL;
	}
	//Eğer arada ise araya ekle
	else
	{
		list *find = *root;
		while (find->next != ptr)
		{
			find = find->next;
			if (find == *root)
				break;
		}

		find->next = temp;
		temp->next = ptr;
		temp = NULL;
		temp = NULL;
	}
}

/*listenin tüm elemanlarını ekrana yazdırır*/
void listinfo(list **root)
{
	if (*root == NULL)
	{
		printf("Listede eleman yok\n");
		return;
	}

	int i = 1;
	list *ptr = *root;
	while (ptr != NULL)
	{
		printf("%d - ", ptr->val);
		ptr = ptr->next;
		i++;
	}
	printf("\n");
}

/*listeyi siler*/
int destroy(list **root)
{
	if (*root == NULL)
	{
		printf("Liste zaten bos\n");
		return -1;
	}
	list *temp;
	while (*root != NULL)
	{
		temp = *root;
		*root = (*root)->next;
		free(temp);
	}
	return 0;
}

int main()
{
	int number[size] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};

	list *root = NULL;

	//Eleman ekle
	for (size_t i = 0; i < size; i++)
	{
		add(&root, number[i]);
	}
	listinfo(&root);
	destroy(&root);
}