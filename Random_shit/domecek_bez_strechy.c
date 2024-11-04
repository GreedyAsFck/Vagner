#include <stdio.h>


short height = 0;
short width = 0;
void width_input(), dole_hore(), boky(), strecha();


int main() {

    printf("Zadejte výšku domu.\n");
    scanf("%hd", &height);
    getchar();

    width_input();
    dole_hore();
    for(int i = 0; i < height -2; i++){
        boky();
    }
    dole_hore();
}

void width_input() {
    printf("Zadejte šířku domu.\n");
    scanf("%hd", &width);
    getchar();

    if( width%2 == 0 || width < 3)
    {
        printf("Neplatná šířka domu. \n Zadejte znovu.\n");
        width_input();
    }
}

void dole_hore() {
    for(int i = 0; i < width; i++){
        printf("X");
    }
    printf("\n");
}

void boky() {
    printf("X");
    for(int i = 0; i < width - 2; i++){
        printf(" ");
    }
    printf("X");
    printf("\n");
}