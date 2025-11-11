#include <stdio.h>
#include <stdlib.h>
#define size 6

typedef struct tree
{
	char name;
	int frequency;
	struct tree *left;
	struct tree *right;
} tree;

typedef struct list
{
	tree *node;
	struct list *next;
} list;

/*queue e eleman gönder*/
int push(list **base, tree *node)
{
	if (*base == NULL)
	{
		*base = (list *)malloc(sizeof(list));
		(*base)->next = NULL,
		(*base)->node = node;
	}
	else
	{
		list *ptr = (*base);
		//son elemana git
		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = (list *)malloc(sizeof(list));
		ptr = ptr->next;
		ptr->next = NULL,
		ptr->node = node;
	}
}

/*queueden en az maliyetli elemanı çıkart*/
int pop(list **base, tree **retval)
{
	if (*base == NULL)
		return -1;
	if ((*base)->next == NULL)
	{
		*retval = (*base)->node;
		free(*base);
		(*base) = NULL;
		return 0;
	}

	list *ptr = (*base);
	list *temp = ptr;
	int cost = ptr->node->frequency;
	//en az maliyetliyi bul
	while (ptr != NULL)
	{
		if ((ptr->node->frequency < cost))
		{
			cost = ptr->node->frequency;
			temp = ptr;
		}
		ptr = ptr->next;
	}
	//bulunan root ise
	if (temp == (*base))
	{
		(*base) = (*base)->next;
		*retval = temp->node;
		free(temp);
		return 0;
	}
	//bulunan sonuncu ise
	else if (temp->next == NULL)
	{
		*retval = temp->node;
		free(temp);

		ptr = *base;
		while (ptr->next != temp)
			ptr = ptr->next;

		ptr->next = NULL;

		return 0;
	}
	//arada biyerde ise
	else
	{
		ptr = (*base);
		while (ptr->next != temp)
			ptr = ptr->next;

		ptr->next = temp->next;
		*retval = temp->node;
		free(temp);
		return 0;
	}
}

int strToint(char *str)
{
	int result = 0;

	while ((*str >= '0') && (*str <= '9') && (*str != '\n'))
	{
		result = (result * 10) + ((*str) - '0');
		str++;
	}
	return result;
}

int createNode(char data[][size], list **base)
{
	for (size_t i = 0; i < size; i++)
	{
		tree *ptr = (tree *)malloc(sizeof(tree));
		ptr->name = data[i][0];
		ptr->frequency = strToint(&data[i][2]);
		ptr->left = NULL;
		ptr->right = NULL;
		push(&(*base), ptr);
	}
}

int createTree(list **base)
{
	if (*base == NULL)
		return -1;

	//ağaç oluştu artık tek bir kök var
	if ((*base)->next == NULL)
		return 0;

	tree *temp1 = NULL, *temp2 = NULL, *ptr = NULL;
	while ((*base)->next != NULL)
	{
		pop(&(*base), &temp1);
		pop(&(*base), &temp2);

		ptr = (tree *)malloc(sizeof(tree));
		ptr->name = '$';
		ptr->frequency = temp1->frequency + temp2->frequency;
		if (temp1->frequency > temp2->frequency)
		{
			ptr->left = temp2;
			ptr->right = temp1;
		}
		else
		{
			ptr->left = temp1;
			ptr->right = temp2;
		}
		push(&(*base), ptr);
	}
}

void inorder(tree *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%c- %d \n ", root->name, root->frequency);
		inorder(root->right);
	}
}

int find(tree *node, char s, int control, char *table)
{
	static int founded = 0;
	if (node != NULL && founded == 0)
	{
		if (node->name == s)
		{
			founded = 1;
			goto line;
		}
		if (founded == 0)
			if (find(node->left, s, 0, table))
				goto line;

		if (founded == 0)
			if (find(node->right, s, 1, table))
				goto line;

		return 0;
	}
	else
		return 0;
line:
	printf("");
	char *ptr = table;
	int length = 1;
	while (*ptr++ != '\n')
		length++;

	realloc(table, length + 1);
	table[length - 1] = control + '0';
	table[length] = '\n';
	if (control == -1)
		founded = 0;

	return 1;
}

char *code(char *str, tree *node)
{
	char *table = (char *)malloc(sizeof(char));
	table[0] = '\n';
	char *s = str;
	while (*s != '\n')
	{
		find(&(*node), *s, -1, table);
		*s++;
	}

	s = table;
	while (*s != '\n')
	{
		printf("%c", *s);
		*s++;
	}
	printf("\n");
}

int decode(char *str, tree *node)
{
	while (*str != '\n')
	{
		tree *ptr = node;
		while (ptr->name == '$')
		{
			if (*str == '0')
				ptr = ptr->left;
			else
				ptr = ptr->right;
			*str++;
		}
		printf("%c", ptr->name);
	}
	printf("\n");
}

int main()
{
	char data[][size] = {"f:5", "e:9", "c:12", "b:13", "d:16", "a:45"};
	list *base = NULL;
	createNode(data, &base);
	createTree(&base);

	printf("kodlanmış metnin çözümle işlemi\n");
	char *s = "100110111000\n";
	decode(s, base->node);
	
	printf("metnin kodlanması işlemi\n");
	code("cefa\n", base->node);

	return 0;
}