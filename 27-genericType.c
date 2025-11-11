#include<stdio.h>
#include <stdlib.h>

struct node {
	void *value;
	struct node *next;
};

struct linkedList {
	struct node *start;
	struct node *end;
};

struct linkedList* LinkedListCreate() {
	struct linkedList *llist = (struct linkedList *) malloc( sizeof(struct linkedList) );
	llist->start = NULL;
	llist->end = NULL;
	return llist;
}

void addNode( struct linkedList *ll, void *value, int size ) {
	if ( NULL == ll->start ) {
		ll->start = (struct node *) malloc( sizeof(struct node) );
		ll->end = ll->start;
	} else {
		ll->end->next = (struct node *) malloc( sizeof(struct node) );
		ll->end = ll->end->next;
	}

	ll->end->value = malloc(size);
	char *pl = ll->end->value;
	char *pv = value;
	while (0<size--)
	{
		*pl = *pv;
		pl++;
		pv++;
	}
	return;
};



int main()
{
	struct linkedList *root = LinkedListCreate();

	//struck gönderme denemesi
	struct my{
	int x;
	char y;
	char *z;
	float f;
	} a = {3,'a',"naber",3.14};
	addNode(root,&a,sizeof(a));
	struct my *b = root->start->value;
	printf("%d \n",b->x);
	printf("%c \n",b->y);
	printf("%s \n",b->z);
	printf("%f \n",b->f);
	
	//float gönderme denemesi, sayı sonradan değiştiriliyor
	//float x =3.14;
	//addNode(root,&x,sizeof(x));
	//x=2;
	
	//float *y= (root->start->value);
	//printf("%f \n",*y);  

}


