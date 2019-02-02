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
    ArrayList b = ArrayList_init();

    for(int i = 0; i<20; ++i) randAndAdd(a, i);

    for(int i = 0; i<5; ++i) randAndAdd(b, i+20);

    ArrayList_addArrayListIndex(b,a,5);

    printf("Size of b: %u\n", ArrayList_size(b));

    for(int i = 0; i<ArrayList_size(b); ++i){
        printf("%d\n", *(int*)ArrayList_get(b,i));
    }

    return 0;
}
