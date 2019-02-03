#ifndef ARRAYLIST_H_INCLUDED
#define ARRAYLIST_H_INCLUDED
#include <stddef.h>

typedef struct ArrayList *ArrayList;

/**creates and returns an ArrayList pointer
<br>If the ArrayList cannot be created because of out of memory issues, the program will exit*/
ArrayList ArrayList_init(void);

/**returns 1 if the element has been added, 0 otherwise
<br>ArrayList should not be null. If it is, then the program will exit.
<br>The void pointer to be added should be malloc'd and NOT MANUALLY FREE'D
<br>Program will exit if out of memory*/
size_t ArrayList_add(ArrayList aL, void * e);

/**Adds the void pointer to the specified index
<br>returns 1 if the element has been added, 0 otherwise
<br>ArrayList should not be null. If it is, then the program will exit.
<br>The void pointed to be added should be malloc'd and NOT MANUALLY FREE'D
<br>Program will exit if out of memory*/
size_t ArrayList_addIndex(ArrayList aL, void *item, const size_t index);

/**returns the void pointer at the index
<br>ArrayList should not be null. If it is, then the program will exit.
<br>if the index is out of bounds, then the program will exit*/
void* ArrayList_get(ArrayList aL, const size_t index);

/**The void pointer is removed from the list and returned for the devs to deal with (free it or whatever)
<br>ArrayList should not be null. If it is, then the program will exit.
<br>if the index is out of bounds, then the program will exit*/
void* ArrayList_removeIndex(ArrayList aL, const size_t index);

/**Loops through the ArrayList to remove the first index that the item is in
<br>If the object exists, then it is removed from the list and the void pointer is returned for the devs to deal with
<br>If the object cannot be found within the list, then NULL is returned*/
void* ArrayList_removeObject(ArrayList aL, const void *item, int (*comp)(const void*, const void *));

/**Returns the size of the array
<br>ArrayList should not be null. If it is, then the program will exit.*/
size_t ArrayList_size(const ArrayList aL);

/**frees up the memory used by the ArrayList and its elements
<br>A custom function is needed to free up any pointers inside structs
<br>Unless you still want all the void pointers to still be valid, they must be free'd using the custom function
<br>The custom function can be NULL if you don't want to free the void pointers yet.
<br>ArrayList should not be null. If it is, then the program will exit.*/
void ArrayList_free(ArrayList aL, void(*custFree)(void*));

/**Sorts the void pointers with a custom compare function
The function will be dealing with DOUBLE VOID POINTERS, so beware
<br>The comp function should not be null. If it is, then the program will exit.*/
void ArrayList_sort(ArrayList aL, int(*comp)(const void *, const void*));

/**Returns the index at which the object is located using bsearch
<br>The ArrayList should be sorted before use, otherwise undefined behavior occurs
<br>If the object is not in the ArrayList, a negative number is returned
<br>ArrayList should not be null. If it is, then the program will exit.
<br>The item should not be null. If it is, then the program will exit.
<br>The comp function should not be null. If it is, then the program will exit.*/
int ArrayList_bSearch(const ArrayList aL, const void *item, int(*comp)(const void*, const void*));

/**Returns the first index of the object
<br>If the object is not found, a negative number is returned
<br>If the ArrayList has been sorted, use the ArrayList_bSearch() function instead
<br>ArrayList should not be null. If it is, then the program will exit.
<br>The item should not be null. If it is, then the program will exit.
<br>The comp function should not be null. If it is, then the program will exit.*/
int ArrayList_indexOf(const ArrayList aL, const void *item, int(*comp)(const void*, const void*));

/**Returns 1 if the ArrayList is empty
<br>If it contains anything, then 0 is returned
<br>ArrayList should not be null. If it is, then the program will exit.*/
size_t ArrayList_isEmpty(ArrayList aL);

/**Adds the void pointers from the second ArrayList into the first
<br>ArrayLists should not be null. If it is, then the program will exit.
<br>The program will exit if out of memory*/
size_t ArrayList_addArrayList(ArrayList first, ArrayList second);

/**Adds the void pointers from the second ArrayList into the first starting from the selected index
<br>ArrayLists should not be null. If it is, then the program will exit.
<br>If the index is out of bounds, the program will exit
<br>The program will exit if out of memory*/
size_t ArrayList_addArrayListIndex(ArrayList first, ArrayList second, size_t index);

/**Returns 1 id the lists are equal, 0 otherwise
<br>If the Lists are both the same size and contains the same elements in the same order, then they are equal
<br>The comp function used should be the same as the one passed into sort and bSearch functions
<br>ArrayLists should not be null. If it is, then the program will exit.
<br>Comp function should not be null. If it is, then the program will exit*/
size_t ArrayList_equals(ArrayList first, ArrayList second, int (*comp)(const void*, const void*));

/**Creates a new ArrayList containing the same elements
<br>ArrayList should not be null. If it is, then the program will exit.*/
ArrayList ArrayList_clone(ArrayList aL);

/**Puts the elements of the ArrayList into the user's array
<br>Only an array of void pointers can be passed in
<br>ArrayLists should not be null. If it is, then the program will exit.
<br>ArrayList should not be null. If it is, then the program will exit.
<br>arrSize should be the Array's actual size or how many elements you want from the list*/
void ArrayList_toArray(ArrayList aL, void *arr[], size_t arrSize);

#endif // ARRAYLIST_H_INCLUDED
