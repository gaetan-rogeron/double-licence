#include <stdio.h>
#include <stdlib.h>

/*FUNCTION*/
void increment(int *a){
    (*a)++;
}

void echange(int *a, int *b){
    int tmp = (*a);
    *a = *b;
    *b = tmp;
}

int trier(int *a, int *b){
    if((*b)<(*a)){
        echange(a,b);
        return 1;
    }
    return 0;
}

/*TEST */
void test_increment(){
    int a = 12;
    printf("avant : %d increment->", a);
    increment(&a);
    printf(" après : %d\n",a);
}

void test_echange(){
    int a = 15;
    int b = 20;
    printf("a= %d, b=%d echange => ",a,b);
    echange(&a,&b);
    printf("a= %d, b=%d \n",a,b);
}

void test_trier(){
    int a = 20;
    int b = 10;
    int res;
    printf("a= %d, b=%d trier => ",a,b);
    res = trier(&a,&b);
    printf("a= %d, b=%d \n",a,b);
    printf("Resultat : %d\n", res);
}

/*MAIN*/
int main(){
    test_increment();
    test_echange();
    test_trier();
    return 0;
}