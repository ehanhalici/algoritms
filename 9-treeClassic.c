/*Burada özellikle binary search tree anlatılmıştır
özellikle rekürsif kullanılmamıştır.*/
#include <stdio.h>
#include <stdlib.h>
#define size 14

typedef struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
} tree;

/*inorder dolaşmak, önce sol alt ağaç sonra root sonra sağ alt ağaç
yani aslında küçükten büyüğe sıralamadır. çift yönlü bağlı liste olmadığında bu fonksiyonu döngülerle ifade etmek için stack kullanmak zorunludur. bununla uğraşmadık */
void inorder(tree *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d - ", root->data);
		inorder(root->right);
	}
}

/* İkili ağaca veri ekleyen fonksiyon */
int insert(tree **node, int data)
{
	if ((*node) == NULL)
	{
		(*node) = (tree *)malloc(sizeof(tree));
		(*node)->data = data;
		(*node)->left = NULL;
		(*node)->right = NULL;
		return 0;
	}
	
	tree *ptr = (*node);
	while (1==1)
	{
		// eklenecek veri node data’sından küçükse
		if (data < ptr->data && ptr->left != NULL)
			ptr = ptr->left;
		// eklenecek veri node data’sından büyük ya da eşitse
		else if((data >= ptr->data && ptr->right != NULL))
			ptr= ptr->right;
		else
			break;
	}
	if (data < ptr->data)
	{
		ptr->left = (tree *)malloc(sizeof(tree));
		ptr= ptr->left;
	}
	else
	{
		ptr->right = (tree *)malloc(sizeof(tree));
		ptr= ptr->right;
	}	
		ptr->data = data;
		ptr->left = NULL;
		ptr->right = NULL;
	return 0;
}

int delete_node(tree **node, int val)
{

	//zaten boşsa çık
	if ((*node) == NULL)
		return 0;

	tree *ptr = (*node);
	//tamp ptr bir önceki yerini tutar
	tree *temp = ptr;
	// düğümü bul
	while (1 == 1)
	{
		if (val == ptr->data)
			break;
		//  veri node data’sından küçükse
		else if (val < ptr->data)
		{
			temp = ptr;
			ptr = ptr->left;
		}
		//  veri node data’sından büyük ya da eşitse
		else if (val >= ptr->data)
		{
			temp = ptr;
			ptr = ptr->right;
		}
		else if (ptr == NULL)
			return -1;
		else
			return -1;
	}
	printf("düğümü bulduk %d önceki %d\n", ptr->data, temp->data);

	//hiç çocuğu yoksa
	if (ptr->left == NULL && ptr->right == NULL)
	{
		if (ptr == temp->left)
			temp->left = NULL;
		else if (ptr == temp->right)
			temp->right =  NULL;
		free(ptr);
		return 0;
	}
	//sadece sağında çocuk varsa
	else if (ptr->left == NULL)
	{
		if (ptr == temp->left)
			temp->left =  ptr->right;
		else if (ptr == temp->right)
			temp->right =  ptr->right;
		else //ptr == root
			*node = ptr->right; 
		free(ptr);
	}
	//sadece solunda çocuk varsa
	else if (ptr->right == NULL)
	{
		if (ptr == temp->left)
			temp->left =  ptr->left;
		else if (ptr == temp->right)
			temp->right =  ptr->left;
		else //ptr == root
			*node = ptr->left; 
		free(ptr);
	}
	// her iki kolunda da çocuklar var ise
	else
	{
		//sağın en küçük değerini bul
		tree *min = ptr->right;
		while (min->left != NULL)
			min = min->left;
		min->left = ptr->left;
		if (ptr == temp->left)
			temp->left = min;
		else if (ptr == temp->right)
			temp->right = min;
		else //ptr == root
			*node = min;

		free(ptr);
	}
}

int main()
{
	int number[size] = {25, 14, 23, 40, 24, 23, 48, 7, 5, 34, 10, 7, 17, 36};
	/*
						25
					/			\
			  14		 			 40
		   /	  \ 			   /	\
		7			23			34		  48
	  /	  \		  /	   \	       \
	5		10	17		24			36
		  /			   /
		7			23
	*/
	tree *root = NULL;

	//Eleman ekle
	for (size_t i = 0; i < size; i++)
	{
		insert(&root, number[i]);
	}

	inorder(root);
	printf("\n");

	delete_node(&root,40);
	inorder(root);
	printf("\n");
}