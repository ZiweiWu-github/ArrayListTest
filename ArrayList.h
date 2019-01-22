#include <stddef.h>
#ifndef ARRAYLIST_H_INCLUDED
#define ARRAYLIST_H_INCLUDED

typedef struct ArrayList *ArrayList;

/**creates and returns an ArrayList pointer*/
ArrayList ArrayList_init(void);

/**returns 1 if the element has been added, 0 otherwise
<br>The void pointer to be added should be malloc'd and NOT MANUALLY FREE'D*/
size_t ArrayList_add(ArrayList aL, void * e);

/**Adds the void pointer to the specified index
<br>returns 1 if the element has been added, 0 otherwise
<br>The void pointed to be added should be malloc'd and NOT MANUALLY FREE'D*/
size_t ArrayList_addIndex(ArrayList aL, void *item, const size_t index);

/**returns the void pointer at the index
<br>if the index is out of bounds, then NULL is returned*/
void* ArrayList_get(ArrayList aL, const size_t index);

/**If the index is within bounds, then the element at that index is removed and its memory freed
<br>Returns 1 is the element was removed, 0 otherwise*/
size_t ArrayList_removeIndex(ArrayList aL, const size_t index);

/**Returns the size of the array*/
size_t ArrayList_size(const ArrayList aL);

/**frees up the memory used by the ArrayList and its elements*/
void ArrayList_free(ArrayList aL);

/**Sorts the void pointers with a custom compare function*/
void ArrayList_sort(ArrayList aL, int(*comp)(const void *, const void*));

/**Returns the index at which the object is located
<br>If the object is not in the ArrayList, a negative number is returned*/
int ArrayList_bSearch(const ArrayList aL, const void *item, int(*comp)(const void*, const void*));

#endif // ARRAYLIST_H_INCLUDED
