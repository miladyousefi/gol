/*Oublions de libérer de la mémoire*/
/* essayer ensuite en utilisant --leak-check=full*/

#include<stdlib.h>


int main(void)

{

    int *p = malloc(sizeof *p);

    if (p != NULL)

        free(p);

    p = malloc(sizeof *p);

    p = NULL;

    return 0;    

}