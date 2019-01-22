#include "ArrayList.h"
#include <stdlib.h>
#include <stdio.h>

struct ArrayList{
    void **list;
    ///size of the malloc
    size_t mallocedSize;
    ///how many elements are in the list
    size_t listSize;
};

ArrayList ArrayList_init(void){
    ArrayList arList = malloc(sizeof * arList);
    if(!arList){
        fprintf(stderr, "The malloc for the ArrayList failed!\n\n");
        exit(1);
    }
    arList->list = malloc(16 * sizeof(void*));
    if(!arList->list){
        fprintf(stderr, "The malloc for the array failed!\n\n");
        exit(1);
    }
    arList->mallocedSize = 16;
    arList->listSize = 0;
    return arList;
}

static size_t mallocCheck(ArrayList aL){
    if(aL->listSize == aL->mallocedSize){
        size_t temp = aL->mallocedSize +16;
        if(temp <= aL->mallocedSize){
            fprintf(stderr, "Cannot make ArrayList any bigger!\n\n");
            return 0;
        }
        else{
            void **tempalloc = realloc(aL->list, temp * sizeof(void*));
            if(!tempalloc){
                fprintf(stderr, "ArrayList realloc failed!\n\n");
                return 0;
            }
            else{
                aL->list = tempalloc;
                aL->mallocedSize = temp;
            }
        }
    }
    return 1;
}

size_t ArrayList_add(ArrayList aL, void *e){
    if(!mallocCheck(aL)) return 0;
    aL->list[aL->listSize++] = e;
    return 1;
}

size_t ArrayList_addIndex(ArrayList aL, void *item, const size_t index){
    if(index > aL->listSize){
        fprintf(stderr, "Array Out of Bounds Exception\nArray size: %d\nTried to add to index: %u\n\n",aL->listSize, index);
        return 0;
    }
    else if(index == aL->listSize) return ArrayList_add(aL, item);
    else{
        if(!mallocCheck(aL)) return 0;
        for(int i = aL->listSize; i > index; --i){
            aL->list[i] = aL->list[i-1];
        }
        aL->list[index] = item;
        return 1;
    }
}

void* ArrayList_get(ArrayList aL, const size_t index){
    if(index >= aL->listSize){
        fprintf(stderr, "Array Out of Bounds Exception\nArray size: %d\nTried to get index: %u\n\n",aL->listSize, index);
        return NULL;
    }
    else return aL->list[index];
}

size_t ArrayList_removeIndex(ArrayList aL, const size_t index){
    if(index >= aL->listSize){
        fprintf(stderr, "Array Out of Bounds Exception\nArray size: %d\nTried to remove index: %u\n\n",aL->listSize, index);
        return 0;
    }
    else{
        --aL->listSize;
        free(aL->list[index]);
        for(size_t i = index; i<aL->listSize; ++i){
            aL->list[i] = aL->list[i+1];
        }
        return 1;
    }
}

size_t ArrayList_removeObject(ArrayList aL, const void *item, int (*comp)(const void*, const void *)){
    for(size_t i = 0; i < aL->listSize; ++i){
        if((*comp)(&item, &aL->list[i]) == 0){
            return ArrayList_removeIndex(aL, i);
        }
    }
    return 0;
}

size_t ArrayList_removeObjectAll(ArrayList aL, const void *item, int (*comp)(const void*, const void *)){
    size_t removed = 0;
    for(size_t i = 0; i < aL->listSize; ++i){
        if((*comp)(&item, &aL->list[i]) == 0){
            ArrayList_removeIndex(aL, i);
            --i;
            removed = 1;
        }
    }
    return removed;
}

size_t ArrayList_size(const ArrayList aL){
    return aL->listSize;
}

void ArrayList_sort(ArrayList aL, int(*comp)(const void *, const void*)){
    qsort(aL->list, aL->listSize, sizeof(void *), comp);
}

void ArrayList_free(ArrayList aL){
    for(size_t i = 0; i<aL->listSize; ++i){
        free(aL->list[i]);
    }
    free(aL->list);
    free(aL);
}

int ArrayList_bSearch(const ArrayList aL, const void *item, int(*comp)(const void*, const void*)){
    void **temp = bsearch(&item, aL->list, aL->listSize, sizeof(void*), comp);
    if(temp) return temp - aL->list;
    else return -1;
}

int ArrayList_indexOf(const ArrayList aL, const void *item, int(*comp)(const void*, const void*)){
    for(size_t i = 0; i< aL->listSize; ++i){
        if((*comp)(&item, &aL->list[i]) == 0){
            return i;
        }
    }
    return -1;
}
