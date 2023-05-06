#include <stdio.h>
#include <math.h>
void minMax(int arr[], int len, int *min, int *max){
    *min = *max = arr[0];
    for (int i = 1; i < len; i++){
        if (arr[i]>*max){
            *max = arr[i];
        }
        if (arr[i]< *min){
            *min = arr[i];
        }
    }
}

typedef struct point{
    int x, y;
} point;

typedef struct rectangle
{
    point ponto1, ponto2;
}rectangle;

int areaRec(rectangle r1){
    int base = fabs(r1.ponto1.x - r1.ponto2.x);
    int altura = fabs(r1.ponto1.y - r1.ponto2.y);
    return base*altura;
}

int *findMid(int a[], int n){
    return &a[n/2];
}
int add(int a[], int len){
    int sum = 0, *p;
    for( p = a; p < a + len; p++){
        sum += *p;
    }
    return sum;
}

int fun(int a, int b){
    return a+b;
}

int func(int array[], int l){
    int s1;
    int s2;
    s2 = 100;
    int i = 0;
    for (int t1 = l; t1!= 0; t1--){
        s1 = array[i];
        s2 = s2 + s1;
        s1 = array[i];
        s2 = s2 + s1;
        i+=2;
    }
    return s2;
}
typedef struct abc{
    int x;
    int y;
}abc;

int main(){
/*  int a[]= {23,4,21,98,987,45,32,10,123,986,50,3,4,5};
   
    int min, max;
    int len = sizeof(a)/sizeof(a[0]);
    
    //printf("Tamanho de a: %ld\nTamanho de a[0]: %ld\nTamanho de len: %d", sizeof(a), sizeof(a[0]), len); //sizeof() mostra quantos bytes tem
    minMax(a, len, &min, &max);
    printf("Menor valor: %d\nMaior valor: %d", min, max);
*/
/*
    int b[] = {1, 2, 3, 4, 5};
    int n = sizeof(b)/sizeof(b[0]);
    int *mid = findMid(b, n);
    printf("Valor do meio: %d\n", *mid);
*/
/*
    int a[] = {1,23,4,5,6};
    char b[] = {'a', 'b', 'c'};
    int *p = &a[1];
    int *q = a;
    char *t = b;
    //printf("Ponteiro para a[0]: %p\nPonteiro para a: %p\n",p, q+1);
    printf("Ponteiro para a[1]: %p\nPonteiro para a[1]-1: %p",p, p-1);
*/   
/*
    int a[] = {1,2,3,4,5,6};
    int *p = &a[2], *q = &a[4];
    printf("%ld\n", q-p);
*/
/*
    int a[] = {11,22,36,5,2};
    int sum = 0, *p;
    for (p = &a[0]; p <= &a[4]; p++){
        sum += *p;
    }
    for (p = a; p <= a + 4; p++){
        sum += *p;
    }
    printf("O valor da soma é: %d\n", sum);
    */
    
/*
    int n = 5;
    int a[n], *p;
    printf("Enter %d elements in the array: ", n);
    for (p=a; p < a+n; p++){
        scanf(" %d", p);
    }

    printf("\nElements in reverse order: ");
    for (p = a + n-1; p >= a; p--)
    {
        printf("%d ", *p);
    }

    printf("\nSum of all the elements in the array: %d", add(a, n));
    */

/*
    int a[2][2] = {{1,2},{3,4}};
    int *p;
    //printf("%d\n", **a);
    for ( p = *a; p <= *a+3; p++){
        printf("%d ", *p);
    }
*/
/*
    int a[][3] = {1, 2, 3, 4, 5, 6};
    int (*ptr)[3] = a;
    printf("%d %d ", (*ptr)[1], (*ptr)[2]);
    ++ptr;
    printf("%d %d ", (*ptr)[1], (*ptr)[2]);
*/
/*
    int (*ptr)(int, int) = fun;
    int a = 5, b = 10;
    int res;
    res = ptr(5,10);
    printf("%d\n", res);
    */
   /*
    abc a = {0,1};
    abc *ptr = &a;

    printf("%d %d", ptr->x, ptr->y);
    return 0;
*/
    rectangle r;
    r.ponto1.x = 3;
    r.ponto1.y = 8;
    r.ponto2.x = 14;
    r.ponto2.y = 2;
    printf("Área do retangulo: %d", areaRec(r));
}