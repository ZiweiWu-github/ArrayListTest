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

static size_t nullCheck(const void* item, const char* itemName, const char* funcName){
    if(!item){
        fprintf(stderr, "Null pointer to %s in %s!\n", itemName, funcName);
        return 1;
    }
    return 0;
}

ArrayList ArrayList_init(void){
    ArrayList arList = malloc(sizeof * arList);
    if(!arList){
        fprintf(stderr, "The malloc for the ArrayList failed!\n\n");
        exit(1);
    }
    arList->list = malloc(16 * sizeof(void*));
    if(!arList->list){
        fprintf(stderr, "The malloc for ArrayList's array failed!\n\n");
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
            exit(1);
        }
        else{
            void **tempalloc = realloc(aL->list, temp * sizeof(void*));
            if(!tempalloc){
                fprintf(stderr, "ArrayList realloc failed!\n\n");
                exit(1);
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
    if(nullCheck(aL, "ArrayList", "ArrayList_add")) exit(1);
    if(!mallocCheck(aL)) exit(1);
    aL->list[aL->listSize++] = e;
    return 1;
}

size_t ArrayList_addArrayList(ArrayList first, ArrayList second){
    if(nullCheck(first, "ArrayList first", "ArrayList_addArrayList")) exit(1);
    if(nullCheck(second, "ArrayList second", "ArrayList_addArrayList")) exit(1);
    for(size_t i = 0; i < second->listSize; ++i){
        ArrayList_add(first, second->list[i]);
    }
    return 1;
}

size_t ArrayList_addIndex(ArrayList aL, void *item, const size_t index){
    if(nullCheck(aL, "ArrayList", "ArrayList_addIndex")) exit(1);
    if(index > aL->listSize){
        fprintf(stderr, "Array Out of Bounds Exception\nArray size: %d\nTried to add to index: %u\n\n",aL->listSize, index);
        exit(1);
    }
    else if(index == aL->listSize) return ArrayList_add(aL, item);
    else{
        if(!mallocCheck(aL)) exit(1);
        for(size_t i = aL->listSize; i > index; --i){
            aL->list[i] = aL->list[i-1];
        }
        aL->list[index] = item;
        ++aL->listSize;
        return 1;
    }
}

size_t ArrayList_addArrayListIndex(ArrayList first, ArrayList second, size_t index){
    if(nullCheck(first, "ArrayList first", "ArrayList_addArrayListIndex")) exit(1);
    if(nullCheck(second, "ArrayList second", "ArrayList_addArrayListIndex")) exit(1);
    for(size_t i =0; i<second->listSize; ++i){
        ArrayList_addIndex(first, second->list[i], index + i);
    }
    return 1;
}

void* ArrayList_get(ArrayList aL, const size_t index){
    if(nullCheck(aL, "ArrayList", "ArrayList_get")){
        exit(1);
    }
    if(index >= aL->listSize){
        fprintf(stderr, "Array Out of Bounds Exception\nArray size: %d\nTried to get index: %u\n\n",aL->listSize, index);
        exit(1);
    }
    else return aL->list[index];
}

void* ArrayList_removeIndex(ArrayList aL, const size_t index){
    if(nullCheck(aL, "ArrayList", "ArrayList_removeIndex")){
        exit(1);
    }
    if(index >= aL->listSize){
        fprintf(stderr, "Array Out of Bounds Exception\nArray size: %d\nTried to remove index: %u\n\n",aL->listSize, index);
        exit(1);
    }
    else{
        --aL->listSize;
        void* t = aL->list[index];
        for(size_t i = index; i<aL->listSize; ++i){
            aL->list[i] = aL->list[i+1];
        }
        return t;
    }
}

void* ArrayList_removeObject(ArrayList aL, const void *item, int (*comp)(const void*, const void *)){
    if(nullCheck(aL, "ArrayList", "ArrayList_removeObject") || nullCheck(item, "item", "ArrayList_removeObject")
       || nullCheck(comp, "comp", "ArrayList_removeObject")){
        exit(1);
    }
    for(size_t i = 0; i < aL->listSize; ++i){
        if((*comp)(&item, &aL->list[i]) == 0){
            return ArrayList_removeIndex(aL, i);
        }
    }
    return NULL;
}

size_t ArrayList_size(const ArrayList aL){
    if(nullCheck(aL, "ArrayList", "ArrayList_size")){
        exit(1);
    }
    return aL->listSize;
}

void ArrayList_sort(ArrayList aL, int(*comp)(const void *, const void*)){
    if(nullCheck(aL, "ArrayList", "ArrayList_removeObject") || nullCheck(comp, "comp", "ArrayList_removeObject")){
        exit(1);
    }
    qsort(aL->list, aL->listSize, sizeof(void *), comp);
}

void ArrayList_free(ArrayList aL, void(*custFree)(void*)){
    if(nullCheck(aL, "ArrayList", "ArrayList_free")){
        exit(1);
    }
    for(size_t i = 0; i<aL->listSize; ++i){
        if(custFree)(*custFree)(aL->list[i]);
    }
    free(aL->list);
    free(aL);
}

int ArrayList_bSearch(const ArrayList aL, const void *item, int(*comp)(const void*, const void*)){
    if(nullCheck(aL, "ArrayList", "ArrayList_bSearch") || nullCheck(item, "item", "ArrayList_bSearch")
       || nullCheck(comp, "comp", "ArrayList_bSearch")){
        exit(1);
    }
    void **temp = bsearch(&item, aL->list, aL->listSize, sizeof(void*), comp);
    if(temp) return temp - aL->list;
    else return -1;
}

int ArrayList_indexOf(const ArrayList aL, const void *item, int(*comp)(const void*, const void*)){
    if(nullCheck(aL, "ArrayList", "ArrayList_indexOf") || nullCheck(item, "item", "ArrayList_indexOf")
       || nullCheck(comp, "comp", "ArrayList_indexOf")){
        exit(1);
    }
    for(size_t i = 0; i< aL->listSize; ++i){
        if((*comp)(&item, &aL->list[i]) == 0){
            return i;
        }
    }
    return -1;
}

size_t ArrayList_isEmpty(ArrayList aL){
    if(nullCheck(aL, "ArrayList", "ArrayList_free")){
        exit(1);
    }
    return !aL->listSize;
}

size_t ArrayList_equals(ArrayList first, ArrayList second, int (*comp)(const void*, const void*)){
    if(nullCheck(first, "ArrayList first", "ArrayList_equals")||nullCheck(second, "ArrayList second", "ArrayList_equals")
       || nullCheck(comp, "comp func", "ArrayList_equals")) exit(1);
    if(first->listSize != second->listSize) return 0;
    for(size_t i = 0; i<first->listSize; ++i){
        if((*comp)(&first->list[i], &second->list[i]) != 0) return 0;
    }
    return 1;
}

ArrayList ArrayList_clone(ArrayList aL){
    if(nullCheck(aL, "ArrayList", "ArrayList_clone")) exit(1);
    ArrayList t = ArrayList_init();
    for(size_t i = 0; i< aL->listSize; ++i){
        ArrayList_add(t, aL->list[i]);
    }
    return t;
}

void ArrayList_toArray(ArrayList aL, void *arr[], size_t arrSize){
    if(nullCheck(aL, "ArrayList", "ArrayList_toArray") || nullCheck(arr, "arr", "ArrayList_toArray")) exit(1);
    for(size_t i = 0; i<aL->listSize && i < arrSize; ++i){
        arr[i] = aL->list[i];
    }
}
