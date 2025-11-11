#include <stdio.h>
#include <stdlib.h>
#include "26-functionPointer.h"
/*
Bu kodda fonksiyon pointerları struckların classmış gibi davranmasını sağladı.
header dosyasını ayrı bir modül olarak derlersek static olan bu fonksiyonlara
doğrudan erişimimiz olmayacak bundan dolayı da sadece struck içinden erişebilrceğiz. 
*/



int main()
{
	string s = contractor();
	s->StringSet(s,"naber");
	printf("%s\n",s->StringGet(s));
}