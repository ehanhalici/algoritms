#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#define size 10000

/*
arr[] = 64 25 12 22 11
tüm diziyi dolaşır ve en küçüğü bulur, ve en baştaki ile yer değiştirir.
11 25 12 22 64
en baştaki en küçük olduğu için artık 2. elemandan başlayarak en küçük arar
11 12 25 22 64
11 12 22 25 64
11 12 22 25 64 
*/
int selection(int arr[], int length)
{
    int tmp, min;

    for (int i = 0; i < length - 1; i++) {
        min = i;

        for (int j = i; j < length; j++) {
            if (arr[j] < arr[min]) {

                min = j;
            }
        }
        tmp = arr[i];
        arr[i] = arr[min];
        arr[min] = tmp;
    }
    return 0;
}

/*
i 0 dan başlar ve her döngüde bir ileri gider
j ise i deki sayıyı alır, geriye doğru giderek sayıyı uygun yere yerleştirir
i deki sayı temp içinde kaydedilir
arr[]=5,4,3,2,1
1. döngü
5 4 3 : i=1 j=0 temp=3 ->j geriye kayar 5 i öne getirir
5 5 3 -> j<0 olduğundan temp değeri j+1 e atanır
4 5 3

2. döngü
3 5 4 : i=2 j=1 temp=4 ->j geriye kayar  5 i öne getirir d[j]=3 key=4 olduğundan durur
3 4 5 : duruduğu yere 4 eklenir
*/
int insertionSort(int arr[], int length)
{
    int temp, i, j;
    for (i = 1; i < length; i++) {
        temp = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
    return 0;
}
/*
First Pass:
( 5 1 4 2 8 ) –> ( 1 5 4 2 8 ), Swap 5 > 1 
  ^ ^ 
( 1 5 4 2 8 ) –> ( 1 4 5 2 8 ), Swap 5 > 4
    ^ ^
( 1 4 5 2 8 ) –> ( 1 4 2 5 8 ), Swap 5 > 2
      ^ ^  
( 1 4 2 5 8 ) –> ( 1 4 2 5 8 ), Not Swap 8 < 8
        ^ ^

Second Pass:
( 1 4 2 5 8 ) –> ( 1 4 2 5 8 )
  ^ ^
( 1 4 2 5 8 ) –> ( 1 2 4 5 8 ), Swap since 4 > 2
    ^ ^
( 1 2 4 5 8 ) –> ( 1 2 4 5 8 )
      ^ ^
( 1 2 4 5 8 ) –> ( 1 2 4 5 8 )
        ^ ^
*/

int bubble(int dizi[], int boy)
{
    int temp;

    for (int i = 1; i < boy; i++) {
        for (int j = 0; j < boy - i; j++) {
            if (dizi[j] > dizi[j + 1]) {
                temp = dizi[j];
                dizi[j] = dizi[j + 1];
                dizi[j + 1] = temp;
            }
        }
    }
    return 0;
}

/*
diziden rasgele bir sayı alınır ve bu sayılardan küçükler ve büyükler olmak üzere dizi sıralanır,
bu süreçte o sayının yeri artık bellidir. daha sonra o sayıdan küçük ve büyk olan sayılar ayrı ayrı tekrar bu algoritmaya gönderilir.
sonuçta küçük sayılar ve büyük sayılar için yine bir sayı seçilir ve ondan büyük ve küçükler sıralanıp iç içie yeniden quicksort çağırılır.

6 5 8 7 9 1   -> ortanca sayı 7 dir büyük ve küçükler olarak iki guruba ayrılır
6 5 1, 7, 9 8 -> bu iki gurup için yeniden algoritma çağırılır
6 5 1         -> ortanca sayı 5 seçtik ve sıralama yaptık
1 5 6         -> sonuç bu
9 8           -> ortanca 9 seçtik ve sıraladık
8 9           -> sonuç bu
hepsini birleşştiriyoruz
1 5 6 7 8 9

*/
void quick(int dizi[], int sol, int sag)
{

    int temp, pivot, i, j;

    if (sol < sag) {
        pivot = sol;
        i = sol;
        j = sag;

        while (i < j) {
            while (dizi[i] <= dizi[pivot] && i < sag)
                i++;

            while (dizi[j] > dizi[pivot])
                j--;

            if (i < j) {
                temp = dizi[i];
                dizi[i] = dizi[j];
                dizi[j] = temp;
            }
        }

        temp = dizi[pivot];
        dizi[pivot] = dizi[j];
        dizi[j] = temp;
        quick(dizi, sol, j - 1);
        quick(dizi, j + 1, sag);
    }
}

/*
Algoritma uygulanırken sayı dizisi en küçük parçalarına ayrılıncaya kadar 2’ye bölünür daha sonra ise birleştirme işlemi yapılır. 
Ancak birleştirme yaparken sıralı bir şekilde birleştiririz. Bu sayede tekrar tek bir parça elde ettiğimizde tam sıralı bir dizi karşımıza çıkar.

                                    38 - 27 - 43 - 3 - 9 - 82 - 10
                                    /                           \
                            38 - 27 - 43 - 3                 9 - 82 - 10
                            /         \                       /       \
                        38 - 27     43 - 3                  9 - 82      10
                        /   \       /    \                  /   \        |
                    38      27     43      3               9     82     10
                      \     /       \     /                 \    /      |
                     27 - 38        3 - 43                  9 - 82      10
                        \             /                        \        /
                        3 - 27 - 38 - 43                     9 - 10 - 82
                                        \                      /
                                    3 - 9 - 10 - 27 - 38 - 43 - 82

*/
void merge(int dizi[], int left, int mid, int right)
{
    // Sayac 
    int i, j, k; 
    // sol dizi boyutu
    int solBoy = mid - left + 1; 
     // sag dizi boyutu
    int sagBoy = right - mid;
    // sol ve sag diziler
    int solDizi[solBoy], sagDizi[sagBoy]; 

    // Asagideki iki for dongusu alt dizileri olusturuyor
    for (i = 0; i < solBoy; i++)
        solDizi[i] = dizi[left + i];
    for (j = 0; j < sagBoy; j++)
        sagDizi[j] = dizi[mid + 1 + j];
    //Sayaclarimiz degistigi icin tekrardan sifirladim. Ama k degerine left degerini verdim...
    i = 0;
    j = 0;
    k = left;
    // soldaki ve sagdaki dizilerin boyutunu asmamasi icin kontrol yaptik
    // sol dizinin ilk elemani sag diziden kucuk veya esitse
    while (i < solBoy && j < sagBoy) { 
        // ustteki diziye soldaki dizinin elemanini atiyoruz
        if (solDizi[i] <= sagDizi[j]) { 
            dizi[k] = solDizi[i];
            i++;
        }
        // degilse sagdaki dizinin elemanini atiyoruz
        else { 
            dizi[k] = sagDizi[j];
            j++;
        }
        k++;
    }
    /* Atama islemleri sonucunda bir dizide eleman kalmissa onlari sira ile yerlestiriyoruz 
    iki dongu de ayni isi yapiyor, biri sol dizi icin digeri sag */
    while (i < solBoy) {
        dizi[k] = solDizi[i];
        i++;
        k++;
    }
    while (j < sagBoy) {
        dizi[k] = sagDizi[j];
        j++;
        k++;
    }
}
// dizi elemanlarini surekli ikiye bolen fonksiyon
void mergeSort(int dizi[], int left, int right)
{
    if (left < right) { // Dizinin ortasindaki elemani buluyoruz.
        int mid = left + (right - left) / 2;
        // Dizinin sol tarafini ikiye boluyoruz
        mergeSort(dizi, left, mid);
        // dizinin sag tarafini ikiye boluyoruz.
        mergeSort(dizi, mid + 1, right);
        //dizinin bolunmus parcalarini siralasin diye mergeSort fonksiyonuna pasliyoruz
        merge(dizi, left, mid, right);
    }
}

int main()
{
    //rasgele sayılarla sıralama işlemi
    int random1[size], random2[size], random3[size], random4[size], random5[size];
    for (int i = 0; i < size; i++) 
        random5[i] = random4[i] = random3[i] = random2[i] = random1[i] = rand() % size;

    clock_t t_selection, t_insertion, t_bubble, t_quick, t_merge;

    t_selection = clock();
    selection(random1, size);
    t_selection = clock() - t_selection;

    t_insertion = clock();
    insertionSort(random2, size);
    t_insertion = clock() - t_insertion;
    
    t_bubble = clock();
    bubble(random3, size);
    t_bubble = clock() - t_bubble;

    t_quick = clock();
    quick(random4, 0, size);
    t_quick = clock() - t_quick;

    t_merge = clock();
    mergeSort(random5, 0, size);
    t_merge = clock() - t_merge;

    printf("\n---random sayilarla---\n\
    selection    %6.3f saniye surdu\n\
    inserton     %6.3f saniye surdu\n\
    bubble       %6.3f saniye surdu\n\
    quick        %6.3f saniye surdu\n\
    merge        %6.3f saniye surdu\n",
        (double)t_selection / CLOCKS_PER_SEC,
        (double)t_insertion / CLOCKS_PER_SEC,
        (double)t_bubble / CLOCKS_PER_SEC,
        (double)t_quick / CLOCKS_PER_SEC,
        (double)t_merge / CLOCKS_PER_SEC);

    //dizili sayılarla sıralama işlemi
    int sequent1[size], sequent2[size], sequent3[size], sequent4[size], sequent5[size];
    for (int i = 0; i < size; i++) 
        sequent1[i] = sequent2[i] = sequent3[i] = sequent4[i] = sequent5[i] = i;

    t_selection = clock();
    selection(sequent1, size);
    t_selection = clock() - t_selection;

    t_insertion = clock();
    insertionSort(sequent2, size);
    t_insertion = clock() - t_insertion;
    
    t_bubble = clock();
    bubble(sequent3, size);
    t_bubble = clock() - t_bubble;

    t_quick = clock();
    quick(sequent4, 0, size);
    t_quick = clock() - t_quick;

    t_merge = clock();
    mergeSort(sequent5, 0, size);
    t_merge = clock() - t_merge;

    printf("\n---dizili sayilarla---\n\
    selection    %6.3f saniye surdu\n\
    inserton     %6.3f saniye surdu\n\
    bubble       %6.3f saniye surdu\n\
    quick        %6.3f saniye surdu\n\
    merge        %6.3f saniye surdu\n",
        (double)t_selection / CLOCKS_PER_SEC,
        (double)t_insertion / CLOCKS_PER_SEC,
        (double)t_bubble / CLOCKS_PER_SEC,
        (double)t_quick / CLOCKS_PER_SEC,
        (double)t_merge / CLOCKS_PER_SEC);

    //ters dizili sayılarla sıralama işlemi
    int reverse1[size], reverse2[size], reverse3[size], reverse4[size], reverse5[size];
    for (int i = 0; i < size; i++) 
        reverse1[i] = reverse2[i] = reverse3[i] = reverse4[i] = reverse5[i] = size - i;

    t_selection = clock();
    selection(reverse1, size);
    t_selection = clock() - t_selection;

    t_insertion = clock();
    insertionSort(reverse2, size);
    t_insertion = clock() - t_insertion;
    
    t_bubble = clock();
    bubble(reverse3, size);
    t_bubble = clock() - t_bubble;

    t_quick = clock();
    quick(reverse4, 0, size);
    t_quick = clock() - t_quick;

    t_merge = clock();
    mergeSort(reverse5, 0, size);
    t_merge = clock() - t_merge;

    printf("\n---ters dizili sayilarla---\n\
    selection    %6.3f saniye surdu\n\
    inserton     %6.3f saniye surdu\n\
    bubble       %6.3f saniye surdu\n\
    quick        %6.3f saniye surdu\n\
    merge        %6.3f saniye surdu\n",
        (double)t_selection / CLOCKS_PER_SEC,
        (double)t_insertion / CLOCKS_PER_SEC,
        (double)t_bubble / CLOCKS_PER_SEC,
        (double)t_quick / CLOCKS_PER_SEC,
        (double)t_merge / CLOCKS_PER_SEC);

    return 0;
}
