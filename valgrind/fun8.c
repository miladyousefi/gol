/* Et avec l'allocation dynamique */
#include<stdlib.h>

#include<stdio.h>


int main(void)

{

    int *i = malloc(sizeof *i);

    if (*i)

    {

        printf("Hello, world !\n");

    }

    return 0;

}