#ifndef ARRAYLIST_H_INCLUDED
#define ARRAYLIST_H_INCLUDED
#include <stddef.h>

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

/**If the index is not valid, then NULL is returned and the list is unchanged
<br>Otherwise, the void pointer is removed from the list and returned for the devs to deal with (free it or whatever)*/
void* ArrayList_removeIndex(ArrayList aL, const size_t index);

/**Loops through the ArrayList to remove the first index that the item is in
<br>If the object exists, then it is removed from the list and the void pointer is returned for the devs to deal with*/
void* ArrayList_removeObject(ArrayList aL, const void *item, int (*comp)(const void*, const void *));

/**Returns the size of the array*/
size_t ArrayList_size(const ArrayList aL);

/**frees up the memory used by the ArrayList and its elements
<br>A custom function is needed to free up any pointers inside structs
<br>Unless you still want all the void pointers to still be valid, they must be free'd using the custom function*/
void ArrayList_free(ArrayList aL, void(*custFree)(void*));

/**Sorts the void pointers with a custom compare function*/
void ArrayList_sort(ArrayList aL, int(*comp)(const void *, const void*));

/**Returns the index at which the object is located using bsearch
<br>If the object is not in the ArrayList, a negative number is returned*/
int ArrayList_bSearch(const ArrayList aL, const void *item, int(*comp)(const void*, const void*));

/**Returns the first index of the object
<br>If the object is not found, a negative number is returned
<br>If the ArrayList has been sorted, use the ArrayList_bSearch() function instead*/
int ArrayList_indexOf(const ArrayList aL, const void *item, int(*comp)(const void*, const void*));

/**Returns 1 if the ArrayList is empty
<br>If it contains anything, then 0 is returned*/
size_t ArrayList_isEmpty(ArrayList aL);

/**Todo:
<br>Adds the void pointers from the second ArrayList into the first*/
size_t ArrayList_addArrayList(ArrayList first, ArrayList second);

/**Todo:
<br>Adds the void pointers from the second ArrayList into the first starting from the selected index*/
size_t ArrayList_addArrayListIndex(ArrayList first, ArrayList second, size_t index);

#endif // ARRAYLIST_H_INCLUDED
