
#include<stdlib.h>


int main(void)

{

    int *p = malloc(3 * sizeof *p);

    if (p != NULL)

    {

        p[-1] = 0;

        free(p);

    }

    return 0;    

}