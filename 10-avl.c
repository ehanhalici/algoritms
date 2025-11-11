#include <stdio.h>
#include <stdlib.h>
#define size 14

typedef struct tree
{
	int data;
	int height; // sürekli yükseklik hesaplamamak için bunu kullandık
	struct tree *left;
	struct tree *right;
} tree;

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

/*ağacık yüksekliğini bulan fonksyion, sağ ve sol ağaç yüksekliklerini bulur ve karşılaştırır, hagisi daha büyük ise onun bir fazlasını döndürür.*/
int height(struct tree *node) 
{ 
    if (node == NULL) 
        return 0; 
    return node->height; 
} 

/*
Balans faktör 1’den büyükse ve eklenen veri ağacın sol çocuğunun datasından küçük ise ağaç sağa döndürülmelidir.

T1, T2, T3, T4 altağaçlardır
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

ana aktörler y ve z dir, y nin sağı z nin solu olur ve y yukarı çıkarak sağına z yi alır
*/
tree *rightRotate(tree *z)
{
	// z düğümünün solu y dir
	tree *y = z->left;
	// y nin sağı olan T3  z nin soluna atanır
	z->left = y->right;
	// son olarak z düğümü y nin sağ çocuğu olarak atanıyor
	y->right = z;
	// Yükseklikler update ediliyor
	z->height = (height(z->left) > height(z->right)) ? height(z->left) + 1 : height(z->right) + 1;
	y->height = (height(y->left) > height(y->right)) ? height(y->left) + 1 : height(y->right) + 1;
	return y;
}

/*
Balans faktör -1’den küçükse ve eklenen veri ağacın sağ çocuğunun datasından büyük ise ağaç sola döndürülmelidir.

  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4

ana aktörler y ve z dir, y nin solu z nin sağı olur ve y yukarı çıkarak soluna z yi alır
*/
tree *leftRotate(tree *z)
{
	//z nin sağı y dir
	tree *y = z->right;
	// y nin solu olan T2  z nin sağına atanır
	z->right = y->left;
	//y nin soluna artık z atanır
	y->left = z;
	//yükseklikler güncelleniyor
	z->height = (height(z->left) > height(z->right)) ? height(z->left) + 1 : height(z->right) + 1;
	y->height = (height(y->left) > height(y->right)) ? height(y->left) + 1 : height(y->right) + 1;
	return y;
}

/*
Balans faktör 1’den büyükse ve eklenen veri ağacın sol çocuğunun datasından büyük ise ağaç ilk olarak sola döndürülmeli, sonra da sağa döndürülmelidir. zigzag durumu vardır bu sorun giderilir.

     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2

y düğümü sola döndürülür ve artık o düğümün başı x olur. z ve onun solu x sağa döndürme işlemi yapılıyor ve x üste çıkıyor z sağ alta iniyor.
*/
tree *leftRightRotate(tree *z)
{
	// y düğümü sola döndürülüyor
	z->left = leftRotate(z->left);
	/* Fonksiyondan geri dönen x düğümü, z düğümünün sol çocuğu olarak atanıyor. Aynı zamanda y düğümünün ebeveyni durumunda */
	// z düğümü bu defa sağa döndürülüyor
	return rightRotate(z);
}

/*
Balans faktör -1’den küçükse ve eklenen veri ağacın sağ çocuğunun datasından küçük ise ağaç ilk olarak sağa döndürülmeli, sonra da sola döndürülmelidir. zigzag durumu vardır bu sorun giderilir.

   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4

y sağa döndürülür ve artık y nin solu olan x üste çıkmış olur, z sola döndürülür ve x en üste çıkar z x in sol çocuğu olur
*/
tree *rightLeftRotate(tree *z)
{
	// y düğümü sağa döndürülüyor
	z->right = rightRotate(z->right);
	/* Fonksiyondan geri dönen x düğümü, z düğümünün sağ çocuğu olarak atanıyor. Aynı zamanda y düğümünün ebeveyni durumunda */
	// z düğümü bu defa sola döndürülüyor
	return leftRotate(z);
}
tree *insert(int x, tree *node)
{
	if (node != NULL)
	{
		// eklenecek verinin kökten büyüklüğüne göre yaprağa kadar iniliyor
		if (x < node->data)
			node->left = insert(x, node->left);
		else if (x > node->data)
			node->right = insert(x, node->right);
		else // Eklenen düğümün adresi geri döndürülüyor
			return node;

		/* Eklemeden sonra her düğümün yüksekliği güncelleniyor, sağ ve sol alt düğümlerin yüksekliklerini karşılaştır, hangisi en yüksek ise onun 1 fazlası yeni yüksekliktir. */

			node->height = (height(node->left) > height(node->right)) ? height(node->left) + 1 : height(node->right) + 1;

			/* Balans faktör 1’den büyükse ve eklenen veri ağacın sol çocuğunun datasından küçük ise ağaç sağa döndürülmelidir. */
			if ((height(node->left) - height(node->right)) > 1 && x < node->left->data)
				return rightRotate(node);

			/* Balans faktör 1’den büyükse ve eklenen veri ağacın sol çocuğunun datasından büyük ise ağaç ilk olarak sola döndürülmeli, sonra da sağa döndürülmelidir. Yani leftRightRotate işlemi uygulanmalıdır. */
			if ((height(node->left) - height(node->right)) > 1 && x > node->left->data)
				return leftRightRotate(node);

			/* Balans faktör -1’den küçükse ve eklenen veri ağacın sağ çocuğunun datasından büyük ise ağaç sola döndürülmelidir. */
			if ((height(node->left) - height(node->right)) < -1 && x > node->right->data)
				return leftRotate(node);

			/* Balans faktör -1’den küçükse ve eklenen veri ağacın sağ çocuğunun datasından küçük ise ağaç ilk olarak sağa döndürülmeli, sonra da sola döndürülmelidir. Yani rightLeftRotate işlemi uygulanmalıdır. */
			if ((height(node->left) - height(node->right)) < -1 && x < node->right->data)
				return rightLeftRotate(node);
	
	}
	else
	{
		node = (tree *)malloc(sizeof(tree));
		node->data = x;
		node->left = NULL;
		node->right = NULL;
		node->height = 1; // new node is initially added at leaf
	}

	return node;
}

/*minimum eleman en soldadır*/
tree *minValue(tree *root)
{
	if (root == NULL)
		return 0;
	while (root->left != NULL)
		root = root->left;
	return (root);
}

/*verilen nod un sağ ve sol yükseklikleri ile denge durumu kontrol edilir*/
int getBalance(tree *origin)
{
	if (origin == NULL)
		return 0;
	return height(origin->left) - height(origin->right);
}

tree *delete (tree *node, int key)
{
	if (node == NULL)
		return node;
	// silinecek veri ebeveyninin verisinden küçükse
	if (key < node->data)
		node->left = delete (node->left, key);
	// silinecek veri ebeveyninin verisinden büyükse
	else if (key > node->data)
		node->right = delete (node->right, key);
	// silinecek veri bulunmuş ise
	else
	{
		//iki çocuğundan en az biri null ise
		if ((node->left == NULL) || (node->right == NULL))
		{
			/* Çocuk yoksa temp NULL değerini alıyor fakat bir çocuk varsa, çocuk temp'e atanıyor */
			tree *temp = node->left ? node->left : node->right;

			// silinecek düğümün hiç çocuğu yoksa
			if (temp == NULL)
			{
				temp = node;
				node = NULL;
			}
			// silinecek düğümün bir çocuğu varsa
			else
				// çocuk ebeveyninin yerine geçiyor
				*node = *temp;
			// temp siliniyor
			free(temp);
		}
		// silinecek düğümün iki çocuğu varsa
		else
		{
			// sağ alt ağacında en küçük veriye sahip olan düğüm bulunuyor
			tree *temp = minValue(node->right);
			// bulunan minimum değer silinecek düğüme kopyalanıyor
			node->data = temp->data;
			/*Artık silinecek değer temp'tedir. Fonksiyon kendisini sağ çocuğu ve Silinecek temp değeriyle tekrar çağırıyor */
			node->right = delete (node->right, temp->data);
		}
	}
	if (node == NULL)
		return node;
	// Ağacın yüksekliği güncelleniyor

		node->height = (height(node->left) > height(node->right)) ? height(node->left) + 1 : height(node->right) + 1;

		// balans 1’den büyükse ve sol alt ağacın balansı 0’dan büyük veya eşitse sağa döndür
		if (getBalance(node) > 1 && getBalance(node->left) >= 0)
			return rightRotate(node);

		//  balans 1’den büyükse ve sol alt ağacın balansı 0’dan küçükse ilk önce sola döndür sonra sağa döndür
		if (getBalance(node) > 1 && getBalance(node->left) < 0)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		//  balans -1’den küçükse ve sağ alt ağacın balansı 0’dan küçük veya eşitse sola döndür
		if (getBalance(node) < -1 && getBalance(node->right) <= 0)
			return leftRotate(node);

		//  balans -1’den küçükse ve sağ alt ağacın balansı 0’dan büyükse ilk olarak sağa döndür sonra sola döndür
		if (getBalance(node) < -1 && getBalance(node->right) > 0)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

	return node;
}

int main()
{
	int number[size] = {25, 14, 23, 40, 24, 23, 48, 7, 5, 34, 10, 7, 17, 36};

	tree *root = NULL;

	//Eleman ekle
	for (size_t i = 0; i < size; i++)
	{
		root = insert(number[i], root);
	}

	inorder(root);
	printf("\n");

	delete (root, 25);
	delete (root, 14);
	delete (root, 7);
	delete (root, 17);

	inorder(root);
	printf("\n");
}