#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

int intComp(const void * i1, const void * i2){
    return **(int**)i1 - **(int**)i2;
}

void custIntFree(void * p){
    free(p);
}

void randAndAdd(ArrayList al, int t){
    int *p = malloc(sizeof *p);
    *p = t;
    ArrayList_add(al, p);
}

int main()
{
    ArrayList a = ArrayList_init();

    for(int i = 0; i<20; ++i) randAndAdd(a, i);
    void *test[20];

    ArrayList_toArray(a, test, 21);

    for(int i = 0; i<20; ++i){
        printf("%d\n", *(int*)test[i]);
    }

    ArrayList_free(a, free);

    return 0;
}
