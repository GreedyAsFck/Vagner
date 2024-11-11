#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void input();

int a, b, c = 0;

void main() {
    
    input();

    int D = pow(b, 2) - 4*a*c;

    if(D > 999 || D < -999) {
        printf("Error: Discriminant out of bounds\n");
        exit(1);
    }
    
    printf("+-------+-------+-------+-------+\n");
    printf("| %5d | %5d | %5d | %5d |\n", a, b, c, D);
    printf("+-------+-------+-------+-------+\n");
    if(D > 0){
        printf("| %29s |\n", "Two real roots");
    }
    else if (D == 0)
    {
        printf("| %29s |\n", "One root");
    }
    else
    {
        printf("| %29s |\n", "The roots are imaginary");
    }
    printf("+-------+-------+-------+-------+\n");
    
}

void input() {
    short kontrola = 0;

    printf("Zadejte a: \n");
    if(scanf("%d", &a) == 1) {
        kontrola++;
    }
    getchar();

    printf("Zadejte b: \n");
    if(scanf("%d", &b) == 1) {
        kontrola++;
    }
    getchar();

    printf("Zadejte c: \n");
    if(scanf("%d", &c) == 1) {
        kontrola++;
    }
    getchar();

    if(kontrola == 3) {
        return;    
    }
    else {
        printf("Error: invalid input");
        exit(1);
    }
}