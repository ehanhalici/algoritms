/*Burada özellikle binary search tree anlatılmıştır
her bir düğümün 2 tane çocuğu vardır.*/
#include <stdio.h>
#include <stdlib.h>
#define size 14

typedef struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
} tree;

/*preorder dolaşmak, önce kök sonra sol alt ağaç sonra sağ alt ağaç */
void preorder(tree *root)
{
	if (root != NULL)
	{
		printf("%d - ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

/*inorder dolaşmak, önce sol alt ağaç sonra root sonra sağ alt ağaç */
void inorder(tree *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d - ", root->data);
		inorder(root->right);
	}
}

/*postorder dolaşmak, önce sol alt ağaç sonra sağ alt ağaç sonra root  */
void postorder(tree *root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d - ", root->data);
	}
}

/* İkili ağaca veri ekleyen fonksiyon */
int insert(tree **node, int data)
{
	if ((*node) != NULL)
	{
		// eklenecek veri node data’sından küçükse
		if (data < (*node)->data)
			insert(&(*node)->left, data);
		// eklenecek veri node data’sından büyük ya da eşitse
		else
			insert(&(*node)->right, data);
	}
	else // eğer ağaç boş ise
	{
		(*node) = (tree *)malloc(sizeof(tree));
		(*node)->data = data;
		(*node)->left = NULL;
		(*node)->right = NULL;
	}
	return 0;
}

/* İkili bir ağacın düğüm sayılarını veren fonksiyon */
int nodeSize(tree *node)
{
	if (node == NULL)
		return 0;
	else
		return nodeSize(node->left) + 1 + nodeSize(node->right);
}

/*ağacık yüksekliğini bulan fonksyion, sağ ve sol ağaç yüksekliklerini bulur ve karşılaştırır, hagisi daha büyük ise onun bir fazlasını döndürür.*/
int height(tree *root)
{	
	if (root == NULL)
		return -1;
	else
	{
		int left_height, right_height;
		left_height = height(root->left);
		right_height = height(root->right);
		if (right_height > left_height)
			return right_height + 1;
		else
			return left_height + 1;
	}
}

/*minimum eleman en soldadır*/
int minValue(tree *root)
{
	if (root == NULL)
		return 0;
	while (root->left != NULL)
		root = root->left;
	return (root->data);
}

/*maximum eleman en sağdadır*/
int maxValue(tree *root)
{
	if (root == NULL)
		return 0;
	while (root->right != NULL)
		root = root->right;
	return (root->data);
}

/*aranan düğümü bulan ve döndüren fonksiyon*/
tree *searchtree(tree *node, int data)
{
	if (node != NULL)
		if (node->data == data)
			return node;
		else if (node->data > data)
			searchtree(node->left, data);
		else
			searchtree(node->right, data);
	else
		return NULL;
}

tree *delete_node(tree *node, int val)
{
	tree *ptr, *temp;
	//zaten boşsa çık
	if (node == NULL)
		return NULL;
	//silinecek düğüm bulunduysa
	if (node->data == val)
	{	//hiç çocuğu yoksa
		if (node->left == NULL && node->right == NULL)
		{
			free(node);
			return NULL;
		}
		else
		{	//sadece sağında çocuk varsa, sağı döndür
			if (node->left == NULL)
			{
				temp = node->right;
				free(node);
				return temp;
			}
			//sadece solunda çocuk varsa, solu döndür
			else if (node->right == NULL)
			{
				temp = node->left;
				free(node);
				return temp;
			}
			// her iki kolunda da çocuklar var ise
			else
			{
				ptr = temp = node->right;
				//sağın en küçük değerini bul
				while (ptr->left != NULL)
					ptr = ptr->left;
				//sağın en küçük değerinin soluna nod un solunu ekle
				//zaten küçük olduğundan bir sorun yok
				// nodun artık solu boş ve sadece sağı var
				ptr->left = node->left;
				//nodu yok et ve sağı tutan temp i geri döndür
				free(node);
				return temp;
			}
		}
	}
	//aranan düğüm bulunması için bu kodlar çalışır, silme işleminin ardında nodeların sağına yada soluna işlem sonucu aktarılır.
	//hiç çocuğu yoksa null döner
	//sadece bir çocuğu varsa o çocuk döner, aradaki node free edilir
	//iki çocuğu varsa yer değişim yapılır
	else if (node->data < val)
		node->right = delete_node(node->right, val);
	else
		node->left = delete_node(node->left, val);
	return node;
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

	printf("node size : %d\n", nodeSize(root));
	printf("tree height: %d\n",height(root));
	root = delete_node(root,14);
	inorder(root);
	printf("\n");

}