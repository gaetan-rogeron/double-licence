#include <stdio.h>
#include <float.h>

float lire_flottant(void) {
    char c;
    float res = 0.0;
    float signe = 1.0;
    float facteur_decimal = 0.1;
    int point_vu = 0;
    int chiffres_apres_virgule = 0;

    printf("FLOTTANT> ");
    while ((c = getchar()) == ' ' || c == '\t');

    if (c == '-') {
        signe = -1.0;
        c = getchar();
    } else if (c == '+') {
        c = getchar();
    }
    while (c != '\n' && c != EOF) {
        if (c >= '0' && c <= '9') {
            if (!point_vu) {
                res = res * 10.0 + (c - '0');
            } else {
	      if (chiffres_apres_virgule < FLT_DIG) { 
                res = res + (c - '0') * facteur_decimal;
                facteur_decimal /= 10.0;
	      }
	      else {
		printf("(Avertissement: précision ignorée) ");
	      }
                chiffres_apres_virgule++;
            }
	    if (res > FLT_MAX) {
                printf("(Avertissement: nombre trop grand) ");
                return FLT_MAX; 
            }
	    
        } 
        else if (c == '.') {
            point_vu = 1;
        } 
        else {
            break; 
        }
        c = getchar();
    }
    
    return res * signe;
}



int main (void){
  float r;
  for (;;){
    r = lire_flottant();
    printf("La valeur est : %f \n",r);
  }
  return 0;
}
