/* la pile d'appel*/

int myMax(int a, int b)

{

    if (a > b)

        return a;

    else

        return b;

}


int myAbs(int a)

{

    return myMax(-a, a);

}


void foo(int *i)

{

    *i = myAbs(*i);

}


int main(void)

{

    int i;

    foo(&i);

    return 0;    

}