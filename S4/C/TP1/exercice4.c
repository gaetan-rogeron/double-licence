#include <stdio.h>

void exercice4(void) {
    int i;
    for (i = 1; i <= 100; i++) {
        printf("%4d ", i);
        if (i % 10 == 0) {
            printf("\n");
        }
    }
}

int main(void){
    exercice4();
    return 0;
}