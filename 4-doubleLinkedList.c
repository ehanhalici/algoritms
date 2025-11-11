#include <stdio.h>
#include <stdlib.h>
#define size 10

typedef struct list
{
	int val;
	struct list *next;
	struct list *prev;
} list;

/*listenin sonuna ekler*/
int addlast(list **root, int key)
{
	if (*root == NULL)
	{
		*root = (list *)malloc(sizeof(list));
		(*root)->val = key;
		(*root)->next = NULL;
		(*root)->prev = NULL;
	}
	else
	{
		list *ptr = (*root);
		list *temp = (list *)malloc(sizeof(list));
		// listenin sonunu bulmamız gerekiyor.
		while (ptr->next != NULL)
			ptr = ptr->next;
		temp->val = key;
		temp->next = NULL;
		temp->prev = ptr;
		ptr->next = temp;
	}
}

/*listenin başına ekler*/
int addhead(list **root, int key)
{
	if (*root == NULL)
	{ // liste yoksa oluşturuluyor
		*root = (list *)malloc(sizeof(list));
		(*root)->val = key;
		(*root)->next = NULL;
		(*root)->prev = NULL;
	}
	else
	{
		list *temp = (list *)malloc(sizeof(list));
		temp->val = key;
		temp->next = *root;
		temp->prev = NULL;
		(*root)->prev = temp;
		*root = temp;
	}
}

int addordered(list **root, int key)
{
	if (*root == NULL)
	{ // liste yoksa oluşturuluyor
		*root = (list *)malloc(sizeof(list));
		(*root)->val = key;
		(*root)->next = NULL;
		(*root)->prev = NULL;
	}
	else
	{
		list *ptr = *root;
		// eklenecek yeri bul
		while (ptr != NULL)
		{
			if (ptr->val > key)
				ptr = ptr->next;
			else
				break;
		}
		//elemanı oluşturalım
		list *temp = (list *)malloc(1 * sizeof(list));
		temp->val = key;
		temp->next = NULL;
		temp->prev = NULL;
		//küçük sayi başa eklenecekse
		if (ptr == *root)
		{
			temp->next = *root;
			temp->prev = NULL;
			(*root)->prev = temp;
			*root = temp;
		}
		//büyük sayi en sona eklenecekse
		else if (ptr == NULL)
		{
			//sondan bir önceki elemana git
			ptr = *root;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			temp->next = NULL;
			temp->prev = ptr;
			ptr->next = temp;
		}
		//araya eklenecekse
		else
		{
			temp->prev = ptr->prev;
			temp->next = ptr;

			ptr->prev->next = temp;
			ptr->prev = temp;
		}
	}
	return 0;
}

/*listeyi ekrana basar*/
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

/*girilen veriyi siler*/
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
	while (ptr != NULL)
	{
		if (ptr->val == key)
		{
			// son elemanı sileceksek
			if (ptr->next == NULL)
			{
				ptr->prev->next = NULL;
				free(ptr);
				return 0;
			}
			// arada bir eleman silinecekse
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			free(ptr);
			return 1;
		}
		ptr = ptr->next;
	}

	printf("Silmek istediğiniz veri bulunamadı\n");
	return 1;
}

int main()
{
	int number[size] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};

	list *root = NULL;

	//Eleman ekle
	for (size_t i = 0; i < size; i++)
	{
		//addhead(&root,number[i]);
		//addlast(&root, number[i]);
		addordered(&root, number[i]);
	}
	listinfo(&root);

	delete (&root, 8);
	listinfo(&root);
}