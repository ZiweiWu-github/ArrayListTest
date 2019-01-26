#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

int intComp(const void * i1, const void * i2){
    return **(int**)i1 - **(int**)i2;
}

void custIntFree(void * p){
    free(p);
}

int main()
{
    ArrayList a = ArrayList_init();

    if(ArrayList_isEmpty(a)){
        printf("Arraylist empty!\n");
    }
    int *p;
    p = malloc(sizeof * p);
    *p = 500;
    ArrayList_add(a, p);

    if(ArrayList_isEmpty(a)){
        printf("Arraylist empty!\n");
    }

//    p = malloc(sizeof * p);
//    *p = 500;
//    ArrayList_add(a, p);

    p = malloc(sizeof * p);
    *p = -1000;
    ArrayList_add(a, p);

    p = malloc(sizeof * p);
    *p = 200;
    ArrayList_add(a, p);

    printf("%d\n", ArrayList_size(NULL));

    ArrayList_sort(a, intComp);
    int b = 500;
    int c = 200;
    printf("%d\n", ArrayList_bSearch(NULL, &b, intComp));

    printf("%d\n", ArrayList_indexOf(NULL, &c, intComp));
    //free(ArrayList_removeIndex(a, 2));
    //free(ArrayList_removeObject(a, &c,intComp ));

    //printf("%d\n", ArrayList_bSearch(a, &b, intComp));
   // printf("%d\n", ArrayList_indexOf(a, &c, intComp));

   // printf("%d\n", ArrayList_size(a));



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
    ArrayList_free(a, custIntFree);
    return 0;
}
