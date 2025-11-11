typedef struct String* string;

struct String
{
	char *str;
	int (*StringLength)(const char* str);
	void (*StringSet)(const void* self_obj, const char* s);
	char* (*StringGet)(const void* self_obj);
};

static int length (char* str)
{
	int i = 1;
	char *p = str;
	while(*(p++) != '\n')
		i++;

	return i;
}

static void set(string self_obj, const char* s)
{
	if (self_obj->str == NULL)
	{
		self_obj->str = (char*)malloc(length(s));
	}
	else
	{
		self_obj->str = (char*)realloc(self_obj->str,length(s));
	}
		char *p1,*p2;
		p1 = self_obj->str;
		p2 = s;
		while (*p2!=NULL)
		{
			*p1=*p2;
			p1++;
			p2++;
		}
}

static char* get(string self_obj)
{
    return self_obj->str;
}

string contractor()
{
	string self = (string)malloc(sizeof(struct String));
	self->str = NULL;
	self->StringLength = &length;
	self->StringSet = &set;
	self->StringGet = &get;
	return self;
}
