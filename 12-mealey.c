#include <stdio.h>
#include <stdlib.h>
#define size 8
typedef struct vertex
{
	char name;
	int edgeCount;
	struct edge *route;
} vertex;

typedef struct edge
{
	struct vertex *nextVertex;
    char in;
    char out;
} edge;

/*bu liste bütün vertex ların adresini tutar, bağlantısı olmayan nodlar kaybolmasın diye yaptık bu işlemi*/
typedef struct list
{
	//dugumun adini tutuyor
	char name;
	// dugumun adresini tutar
	struct vertex *address;
	struct list *next;
} list;

/*nodeları listeye ekler*/
void insertList(list **root, vertex *node)
{
	if ((*root) == NULL)
	{
		(*root) = (list *)malloc(sizeof(list));
		(*root)->name = node->name;
		(*root)->address = node;
		(*root)->next = NULL;
	}
	else
	{
		list *ptr = (*root);
		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = (list *)malloc(sizeof(list));
		ptr = ptr->next;
		ptr->name = node->name;
		ptr->address = node;
		ptr->next = NULL;
	}
}

/*nodeların tutulduğu listeyi ekrana basar*/
void showList(list **root)
{
	list *ptr = *root;

	while (ptr != NULL) // (!ptr)
	{
		printf("node name : %c, address : %d\n", ptr->name, ptr->address);
		ptr = ptr->next;
	}
	printf("\n");
}

void nodeLink(char node1, char node2, list **root, char in,char out)
{
	list *ptr = *root;
	vertex *temp1 = NULL, *temp2 = NULL;
	while (ptr != NULL)
	{
		if (ptr->name == node1)
			temp1 = (vertex *)ptr->address;
		if (ptr->name == node2)
			temp2 = (vertex *)ptr->address;
		ptr = ptr->next;
	}
	// daha önce hiçbir bağlantı yapılmamışsa
	if (temp1->edgeCount == 0)
	{
		temp1->route = (edge *)malloc(sizeof(edge));
		temp1->route[temp1->edgeCount].nextVertex = temp2;
        temp1->route[temp1->edgeCount].in = in;
        temp1->route[temp1->edgeCount].out = out;
		temp1->edgeCount++;
	}
	// daha önce bir bağlantı yağılmışsa ozaman realloc kullanırız, edgeCount + 1 tane
	else
	{
		temp1->route = realloc((edge *)temp1->route, (temp1->edgeCount + 1) * sizeof(edge));
		temp1->route[temp1->edgeCount].nextVertex = temp2;
        temp1->route[temp1->edgeCount].in = in;
        temp1->route[temp1->edgeCount].out = out;
		temp1->edgeCount++;
	}
}

/*node varsa oluşturmaz sadece varsa oluşturur*/
void createNode(char nodeName, list **root)
{
	//varlık kontrolü
	list *ptr = *root;
	while (ptr != NULL)
	{
		if (ptr->name == nodeName)
			return;
		ptr = ptr->next;
	}

	vertex *temp = (vertex *)malloc(sizeof(vertex));
	temp->name = nodeName;
	temp->edgeCount = 0;
	temp->route = NULL;
	insertList(&(*root), temp);
}

void parser(char *str[], list **root)
{
	for (size_t i = 0; i < size; i++)
	{
		createNode(str[i][0], &(*root));
		createNode(str[i][7], &(*root));
		nodeLink(str[i][0], str[i][7], &(*root),str[i][2],str[i][5]);
	}
}

/*nodelar arasında gezebildiğimiz fonksiyon*/
void travel(list **root)
{
	vertex *ptr = (*root)->address;
	char select;
	while (1 == 1)
	{
		printf("active node is %c\n", ptr->name);
		for (size_t i = 0; i < ptr->edgeCount; i++)
			printf("%c -%c> %c \n", ptr->name, ptr->route[i].in, (ptr->route[i].nextVertex)->name);
		printf("select input:");
		fflush(stdin);
		scanf(" %c", &select);
		if (select == '!')
			break;
		for (size_t i = 0; i < ptr->edgeCount; i++)
		{
			if (ptr->route[i].in == select)
			{
                printf("output->%c\n",ptr->route[i].out);
				ptr = (ptr->route[i].nextVertex);
				break;
			}
		}
	}
}
int main()
{
	char *str[] = {"a-0><0-b", "a-1><1-c", "b-0><1-b", "b-1><0-d", "c-0><0-c", "c-1><1-d", "d-0><0-a","d-1><0-b"};
	list *root = NULL;

	parser(str, &root);
	showList(&root);
	travel(&root);
}
