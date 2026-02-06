#include <stdio.h>

int chercher_caractere(char chaine[], char symbole){
    int i = 0;
    while (chaine[i] != '\0'){
        if (chaine[i] == symbole){
            return 1;
        }
        i++;
    }
    return 0;
}

int egale(char chaine1[], char chaine2[]){
    int i=0;
    int j=0;
    int n=0;
    while(chaine1[i] != '\0'){
        i++;
    }
    while(chaine2[j] != '\0'){
        j++;
    }
    printf("i : %d, j : %d\n",i,j);
    if (i==j){
        while (n<=j){
            if(chaine1[n] != chaine2[n]){
                return 0;
            }
            n++;
        }
        return 1;
    }
    return 0;
}

void miroir(char chaine[]){
    int i=0;
    int j;
    while(chaine[i] != '\0'){
        i++;
    } 
    for(j=i;j>=0;j--){
        printf("%c",chaine[j]);
    }
    printf("\n");
    
}

int inclue(char chaine[], char sous_chaine[]){
    
}

void question1(){
    char chaine1[] = "efgp";
    char symbole1;
    int res;

    symbole1 = 'g';
    res = chercher_caractere(chaine1,symbole1);
    printf(" chaine : 'e','f','g','p'\n symbole : 'g'\n resultat : %d\n",res);
}

void question2(){
    char chaine1[] = "ag4";
    char chaine2[] = "ag4";
    char chaine3[] = "3fc";
    char chaine4[] = "wth";
    printf("chaine1[3] = {'a','g','4'}  chaine2[3] = {'a','g','4'}\nresulat : %d\n",egale(chaine1,chaine2));
    printf("chaine3[3] = {'3','f','c'}   chaine4[3] = {'w','t','h'}\nresulat : %d\n",egale(chaine3,chaine4));
}

void question3(){
    printf("marie\n");
    miroir("marie");
    printf("Hello, World!\n");
    miroir("Hello, World!");
}

int main(){
    question1();
    question2();
    question3();
    return 0;
}