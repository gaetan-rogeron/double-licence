#include <stdio.h>
#include <limits.h>


int lire_entier(void){
    char c;
    int resultat = 0;
    int valide = 1;
    int chiffre = 0;

    printf("ENTIER> ");

    while ((c= getchar()) != '\n' && c!= EOF){
        if (c>='0' && c<='9'){
            resultat = resultat * 10 + (c - '0');
            chiffre = 1;
        }
        else {
            valide=0;
        }
     
    }
    if (valide == 1 && chiffre == 1){
        return resultat;
    }
    else {
        return -1;
    }
    return 0;

}


int somme(int a, int b){
  int result;
  result = a+b;
  if (result > INT_MAX){
    return -1;
  }
  else {
    return result;
  }
}

int fibo_naif(int n){
  int i;
  int u0 = 0;
  int u1 = 1;
  int tmp;
  
  if (n==0){return 0; }
  else if (n==1){ return 1;}
  
  for (i=1;i<=n;i++){
    tmp = somme(u0,u1);
    u0 = u1;
    u1 = tmp;
  }
  return u0;
}

int fibonnacci(int n){
  int i;
  int u0 = 0;
  int u1 = 1;
  int tmp;
  
  if (n==0){return 0;}
  else if (n==1){ return 1;}
  
  for (i=1;i<=n;i++){
    tmp = somme(u0,u1);
    if (tmp > INT_MAX){
      return -1;
    }
    u0 = u1;
    u1 = tmp;
  }
  return u0;
}

int main(void){
  int valeur;
  int r;
  for (;;){
    valeur = lire_entier();
    r= fibonnacci(valeur);
    printf("fibo(%i) : %i \n",valeur,r);
  }
  return 0;
 
}
