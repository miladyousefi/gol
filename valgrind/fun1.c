/* Invalid read/write Déréférençons NULL */

#include<stdlib.h>


int main(void)

{

    int *p = NULL;

    *p = 0;

    return 0;    

}