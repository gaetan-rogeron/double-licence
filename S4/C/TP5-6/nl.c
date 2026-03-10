#include <stdio.h>
#include <stdlib.h>

void print_file(FILE *fichier){
    char c;
    int i;
    int debut_ligne = 1;
    i=1;
    while ( (c=getc(fichier)) != EOF) {
        if (debut_ligne){
            printf("%d: ", i);
            i++;
            debut_ligne = 0;
        }
        if (c == '\n'){
            debut_ligne= 1;
        }
        fputc(c, stdout);

    };
}

int main(int argc, char* argv[]){
    int i;
    FILE * fichier;
    char * nom_fichier;
    if (argc==1) { 
        print_file(stdin);
    } 
    else {
        for (i=1; i<argc; i++) {
            nom_fichier = argv[i];
            if ((fichier=fopen(nom_fichier,"r")) == NULL) {
                fprintf(stderr,"Erreur lecture %s\n",nom_fichier);
                exit(1);
        }
        print_file(fichier);
        fclose(fichier);
        }
    }
    return 0;
}