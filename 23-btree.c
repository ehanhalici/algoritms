/*
B-Ağacının tanımı
Her düğümün (node) en fazla m çocuğu bulunmalıdır. (Bu sayının üzerinde eleman bulunursa düğümün çoğaltılması gerekir)
Kök (root) ve yaprak (leaf) düğümleri haricindeki her düğümün en az m/2 adet elemanı bulunmalıdır. (Bu sayının altında eleman bulunursa düğüm kaldırılır)
Bütün yapraklar aynı seviyede olmak zorundadır. Bir yaprağın seviyesinin düşmesi durumunda (daha yukarı çıkması veya daha sığ olması durumunda) ağaçta yapısal değişiklik gerekir.
Herhangi bir düğümde k çocuk bulunuyorsa k-1 elemanı gösteren anahtar (key) bulunmalıdır.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2
#define size 14

struct btree
{
	int count;
	int value[MAX + 1];
	struct btree *link[MAX + 1];
};

struct btree *root;

// Insert node
void insertNode(int value, int location, struct btree *node, struct btree *child)
{
	int j = node->count;
	//doğru pozisyona eklemek için kaydırma yap
	while (j > location)
	{
		node->value[j + 1] = node->value[j];
		node->link[j + 1] = node->link[j];
		j--;
	}
	//doğru pozisyona ekle
	node->value[j + 1] = value;
	node->link[j + 1] = child;
	node->count++;
}

// Split node
void splitNode(int value, int *pval, int location, struct btree *node, struct btree *child, struct btree **newNode)
{
	int median, j;

	if (location > MIN)
		median = MIN + 1;
	else
		median = MIN;

	*newNode = (struct btree *)malloc(sizeof(struct btree));
	j = median + 1;
	while (j <= MAX)
	{
		(*newNode)->value[j - median] = node->value[j];
		(*newNode)->link[j - median] = node->link[j];
		j++;
	}
	node->count = median;
	(*newNode)->count = MAX - median;

	if (location <= MIN)
	{
		insertNode(value, location, node, child);
	}
	else
	{
		insertNode(value, location - median, *newNode, child);
	}
	*pval = node->value[node->count];
	(*newNode)->link[0] = node->link[node->count];
	node->count--;
}

// Set the value
int setValue(int value, int *pval, struct btree *node, struct btree **child)
{
	//node null ise child i null yap ve geri dön
	int location;
	if (!node)
	{
		*pval = value;
		*child = NULL;
		return 1;
	}
	//ilk konumda ise location 0
	if (value < node->value[1])
	{
		location = 0;
	}
	else
	{ //ilk konumda değilse konumunu belirle
		for (location = node->count; (value < node->value[location] && location > 1); location--)
			;
		//aynı elemandan iki tane olamaz kontrolü
		if (value == node->value[location])
		{
			printf("Duplicates are not permitted\n");
			return 0;
		}
	}
	//setvalue işlevi uygun pozisyondaki poiner için tekrar çağrılır. null ise ilk if içine girer ve child null döner
	//null değil ise null olana kadar doğru pozisyondaki pointer ile aşağıya inilir.
	//if in içine girdiğinde birkaç katman recursive işlemi gerçekleşmiş olabilir birazdan geri çıkacağız
	if (setValue(value, pval, node->link[location], child))
	{	//tam dolum yoksa normal ekleme yapılır
		if (node->count < MAX)
		{
			insertNode(*pval, location, node, *child);
		}
		//eklenecek yer dolmuşsa bölme yapılması gerekir. bölmenin sonucunda child değerleri ve yukarı eklenecek sayı belirlenir
		// return 1 ile bir üst recursive ye çıkılır
		else
		{	
			splitNode(*pval, pval, location, node, *child, child);
			return 1;
		}
	}
	return 0;
}

// Insert the value
void insert(int value)
{
	int pval;
	struct btree *child;

	if (setValue(value, &pval, root, &child))
	{
		// Create a node
		struct btree *newNode;
		newNode = (struct btree *)malloc(sizeof(struct btree));
		newNode->value[1] = pval;
		newNode->count = 1;
		newNode->link[0] = root;
		newNode->link[1] = child;
		root = newNode;
	}
}

// Search node
void search(int value, int *location, struct btree *myNode)
{
	if (!myNode)
	{
		return;
	}

	if (value < myNode->value[1])
	{
		*location = 0;
	}
	else
	{
		for (*location = myNode->count; (value < myNode->value[*location] && *location > 1); (*location)--)
			;
		if (value == myNode->value[*location])
		{
			printf("%d is found", value);
			return;
		}
	}
	search(value, location, myNode->link[*location]);

	return;
}

// Traverse then nodes
void traversal(struct btree *myNode)
{
	int i;
	if (myNode)
	{
		for (i = 0; i < myNode->count; i++)
		{
			traversal(myNode->link[i]);
			printf("%d ", myNode->value[i + 1]);
		}
		traversal(myNode->link[i]);
	}
}

int main()
{
	int value, ch;

	int number[size] = {3, 14, 23, 40, 24, 25, 48, 7, 5, 34, 10, 6, 17, 36};

	//Eleman ekle
	for (size_t i = 0; i < size; i++)
	{
		printf("%d ekleniyor\n", number[i]);
		insert(number[i]);
	}

	traversal(root);

	printf("\n");
	search(11, &ch, root);
}
