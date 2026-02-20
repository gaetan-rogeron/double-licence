#include <stdio.h>
#include <stdlib.h>

/*FUNCTION*/
int longueur(char *c){
    int i;
    i=0;
    while(c[i]!='\0'){
           i++;
    }
    return i;
}
/*
char * copie_chaine(char *c){
    char *p;
    p = &c;
    return *p;
}
*/

/*TEST*/
void test_longueur(){
    char *c = "Hello, World!";
    int res;
    res = longueur(c);
    printf("chaine : %s, longueur : %d\n", c, res);

}
/*
void test_copie(){
    char *res;
    char *c = "Lebron James";

    res = copie_chaine(c);
    printf ("*c = %s, *res= %s",c, res);
}
*/
/*MAIN*/
int main(){
    test_longueur();
    /*test_copie();*/
    return 0;
}
