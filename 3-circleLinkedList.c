#include <stdio.h>
#include <stdlib.h>
#define size 10

typedef struct list
{
	int val;
	struct list *next;
} list;

/*dairesel listenin baş tarafına ekleme yapar*/
int addfront(list **root, int key)
{
	if (*root == NULL)
	{
		*root = (list *)malloc(sizeof(list));
		(*root)->val = key;
		(*root)->next = *root;
	}
	else
	{
		list *temp = (list *)malloc(sizeof(list));
		list *ptr = *root;
		temp->val = key;
		// listenin son elemanı bulunuyor.
		while (ptr->next != *root)
			ptr = ptr->next;
		temp->next = *root;
		ptr->next = temp;
		*root = temp;
	}
}

/*dairesel listenin son tarafına ekleme yapar*/
int addlast(list **root, int key)
{
	if (*root == NULL)
	{
		*root = (list *)malloc(sizeof(list));
		(*root)->val = key;
		(*root)->next = *root;
	}
	else
	{
		list *temp = (list *)malloc(sizeof(list));
		list *ptr = *root;
		temp->val = key;
		// listenin son elemanı bulunuyor.
		while (ptr->next != *root)
			ptr = ptr->next;
		temp->next = *root;
		ptr->next = temp;
	}
}

/*aranan nodu döndüren fonksiyon*/
list *find(list **root, int key)
{
	if (*root == NULL)
	{
		printf("liste boş\n");
		return NULL;
	}
	
	list *founded = NULL;
	list *temp = (*root);
	do
	{
		if (temp->val != key)
			temp = temp->next;
		else
		{
			founded = temp;
			break;
		}
	} while ((*root) != temp);
	return founded;
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
	list *ptr = (*root)->next;
	//sonrası root oluncaya kadar git
	printf("%d - ", (*root)->val);
	while (ptr != *root)
	{
		printf("%d - ", ptr->val);
		ptr = ptr->next;
		i++;
	}
	printf("\n");
}

/*listedeki elemanı siler*/
int delete (list **root, int key)
{
	if (*root == NULL)
	{
		printf("Listede eleman yok\n");
		return 0;
	}
	if ((*root)->next ==*root )
	{
		if ((*root)->val ==key)
		{
			free(*root);
			*root=NULL;
		}
		else
			printf("eleman bulunamadı");
		return 0;
	}
	//listede birden çok eleman varsa
	else
	{
		list *ptr = *root;
		while (ptr->next->val != key)
		{
			if (ptr->next->next == *root)
			{
				printf("Silmek istediginiz veri bulunmamaktadir.\n\n");
				return -1;
			}
			ptr = ptr->next;
		}
		list *temp = ptr->next;
		ptr->next = ptr->next->next;
		free(temp);
	}
	
	return 0;
}

/*listeyi siler*/
int destroy(list **root)
{
	if (*root == NULL)
	{
		printf("Liste zaten bos\n");
		return -1;
	}

	if ((*root)->next == *root)
	{
		free(*root);
		*root =NULL;
		return 0;
	}

	//sona git
	list *ptr = *root;
	while (ptr->next != *root)
		ptr = ptr->next;

	//son elemana kadar bir kayarak temizle
	list *temp;
	printf("siliniyor ... ");
	while ((*root) != ptr)
	{
		temp = *root;
		*root = (*root)->next;
		printf("%d - ", temp->val);
		free(temp);
	}
	//son elemanı temizle
	printf("%d silindi\n", (*root)->val);
	free((*root));
	//dairesel bağlı listelerde görülen kronik sorun
	*root = NULL;
	return 0;
}

int main()
{
	int number[size] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};

	list *root = NULL;

	//Eleman ekle
	for (size_t i = 0; i < size; i++)
	{
		addfront(&root, number[i]);
		//addlast(&root, number[i]);
	}
	listinfo(&root);

	delete (&root, 7);
	listinfo(&root);

	list *founded = find(&root, 5);
	if (founded !=NULL)
		printf("%d nin adresi %p\n", founded->val, founded);

	destroy(&root);
	listinfo(&root);
}