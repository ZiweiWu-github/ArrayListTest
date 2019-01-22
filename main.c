#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

int intComp(const void * i1, const void * i2){
    return **(int**)i1 - **(int**)i2;
}

int main()
{
    ArrayList a = ArrayList_init();
    int *p;
    p = malloc(sizeof * p);
    *p = 500;
    ArrayList_add(a, p);

    p = malloc(sizeof * p);
    *p = 500;
    ArrayList_add(a, p);

    p = malloc(sizeof * p);
    *p = -1000;
    ArrayList_add(a, p);

    p = malloc(sizeof * p);
    *p = 200;
    ArrayList_add(a, p);

    printf("%d\n", ArrayList_size(a));

    ArrayList_sort(a, intComp);
    int b = 500;
    int c = 200;
    printf("%d\n", ArrayList_bSearch(a, &b, intComp));
    printf("%d\n", ArrayList_indexOf(a, &c, intComp));

    ArrayList_removeObjectAll(a, &b, intComp);
    printf("%d\n", ArrayList_bSearch(a, &b, intComp));

    printf("%d\n", ArrayList_size(a));


//    for(int i = 0; i<1000000; ++i){
//        if(!ArrayList_add(a, malloc(1)));
//        ///printf("Adding #%d\n", i);
//    }
//
//
//
//    if(!ArrayList_removeIndex(a,1000000)){
//        printf("ARRAYS START AT 0!!!\n");
//    }
//
//    printf("%d\n", ArrayList_size(a));
//
//
//    if(ArrayList_get(a,9999999)){
//        printf("ARRAYS START AT 0!!!");
//    }
    ArrayList_free(a);
    return 0;
}
