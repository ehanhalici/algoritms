#include <stdio.h>

void ikiliyaz(int x)
{
	int i = sizeof(int) * 8 - 1;

	for (; i >= 0; --i)
	{	//x i i kadar kaydır 1 ile "ve" le
		if (x >> i & 1 == 1) 
			putchar('1');
		else
			putchar('0');
		if (i % 4 == 0)
			putchar(' ');
	}
	printf("\n");
}

int sifirla(int a, int start, int end)
{
	int k;
	for (k = start; k <= end; k++)
	//1 i k kadar kaydırıp değilini al, ayni 0 yap ve x ile "ve" işlemine sok, x i 0 la "ve"lemek o biti 0 lar
		a &= ~(1 << k); 
	return a;
}

int birle(int a, int start, int end)
{
	int k;

	for (k = start; k <= end; k++)
	//1 i k kadar kaydırıp a ile "veya"larsan o bit 1 olur
		a |= 1 << k; 
	return a;
}

int bityaz(int a, int start, int end, int value)
{
	//değeri başlayacağı yer kadar sola kaydır ve ata
	int temp = value << start; 
	//dosyanın baş ve son kısmını sıfırla
	a = sifirla(a, start, end); 
	//dosyanın 0 değerleriyle tepm in kaymış değerlerini "veya"latıp dosyaya ata
	a |= temp; 
	return a;
}

int bitoku(int a, int start, int end)
{
	//dosyayı başlangıç kadar sağa kaydırır, günde hiç kaydırmaz ayda 4, yılda 8 kaydırır
	int temp = a >> start; 
	temp = sifirla(temp, end - start + 1, sizeof(int) * 8 - 1);
	//burası gün ay yada yıl olan bit değilde ondan bi fazlasından sonuna kadar sıfırlar aradaki farkın bir fazlası aradaki farktır
	return temp; 
}

int main()
{
	int gun, ay, yil;
	int data = 0;

	printf("Tarihi Giriniz \n");
	printf("Gun : ");
	scanf("%d", &gun); //   [0000 0000  0000 0000  0000 0000  000*0 0100]
	printf("Ay  : ");
	scanf("%d", &ay); //   [0000 0000  0000 0000  0000 0000  0000* 0011]
	printf("Yil : ");
	scanf("%d", &yil); //   [0000 0000  0000 0000  0000 0000  *0111 0100]
	yil = yil - 1900;

	//ikiliyaz(data);
	//gün değerin start kadar sola kaydır data ile veyala
	data = bityaz(data, 0, 4, gun); 
	//ikiliyaz(data);
	data = bityaz(data, 5, 8, ay);
	//ikiliyaz(data);
	data = bityaz(data, 9, 16, yil);
	//ikiliyaz(data);

	printf("\nData :%d\n", data);

	gun = bitoku(data, 0, 4);
	ay = bitoku(data, 5, 8);
	yil = bitoku(data, 9, 16);

	printf("\nGun :%d  Ay:%d  Yil:%d\n", gun, ay, yil + 1900);
	return 0;
}
