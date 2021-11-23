/*depassement du tableau*/
#include<stdlib.h>


int main(void)

{

    int *p = malloc(3 * sizeof *p);

    if (p != NULL)

    {

        p[3] = 0;

        free(p);

    }

    return 0;    

}