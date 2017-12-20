#include <stdio.h>

int varInt = 2;
int varInt2 = 3;
float varFloat = 1.1;
float varFloat2 = 9.9;
char varChar = 9;
char varChar2 = 'b';

void func();

int main(){

    printf("Ola\n");

}

void func(){

    varFloat = 1 + 3;
    varFloat = 1 - 3;
    varFloat = 1 * 3;
    varFloat = 1 / 3;

}
