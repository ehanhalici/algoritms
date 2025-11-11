#include <stdio.h>
#include <stdlib.h>
#define size 10

typedef struct list
{
	int val;
	struct list *next;
} list;

/*listenin başına eleman ekler*/
int addhead(list **root, int key)
{
	if (*root == NULL)
	{
		*root = (list *)malloc(sizeof(list));
		(*root)->val = key;
		(*root)->next = NULL;
		return 1;
	}

	list *ptr = NULL;

	ptr = (list *)malloc(sizeof(list));

	ptr->next = *root;
	ptr->val = key;

	*root = ptr;
}

/*listenin sonuna eleman ekler*/
int addlast(list **root, int key)
{
	if (*root == NULL)
	{
		*root = (list *)malloc(sizeof(list));
		(*root)->val = key;
		(*root)->next = NULL;
		return 1;
	}

	list *ptr = *root;

	while (ptr->next != NULL)
		ptr = ptr->next;

	ptr->next = (list *)malloc(sizeof(list));
	ptr = ptr->next;

	ptr->next = NULL;
	ptr->val = key;

	return 1;
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

/*listenin eleman sayısını verir*/
int count(list *root)
{
	int counter = 0;
	list *ptr = root;
	while (ptr != NULL)
	{ // ptr->next!=NULL koşulu olsaydı son düğüm sayılmazdı
		counter++;
		ptr = ptr->next;
	}
	return counter;
}

/*listede ilgili elemanın nodunu döndürür*/
list *find(list **root, int key)
{
	if (*root == NULL)
	{
		printf("liste boş\n");
		return NULL;
	}

	if (*root == NULL)
		return NULL;

	list *ptr = *root;

	while (ptr != NULL)
	{
		if (ptr->val != key)
			ptr = ptr->next;
		else
			break;
	}

	return ptr;
}

/*listedeki elemanı siler*/
int delete (list **root, int key)
{
	if (*root == NULL)
	{
		printf("Listede eleman yok\n");
		return -1;
	}
	if ((*root)->val == key)
	{
		list *temp = *root;
		*root = (*root)->next;
		free(temp);
		return 0;
	}

	list *ptr = *root;
	while (ptr->next != NULL)
	{
		if (ptr->next->val == key)
		{
			list *temp = ptr->next;
			ptr->next = temp->next;
			free(temp);
			return 1;
		}
		ptr = ptr->next;
	}

	printf("Silmek istediğiniz veri bulunamadı\n");
	return 1;
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
		//addhead(&root,number[i]);
		addlast(&root, number[i]);
	}
	listinfo(&root);

	delete (&root, 2);
	listinfo(&root);

	list *founded = find(&root, 5);
	if (founded != NULL)
		printf("%d address : %p\n", founded->val, founded);

	printf("%d tane eleman var\n", count(root));

	destroy(&root);
	listinfo(&root);
}