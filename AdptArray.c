#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

struct AdptArray_ {
    PElement* elements;
    int size;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
};

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
    PAdptArray adptArray = malloc(sizeof(struct AdptArray_));
    if (!adptArray) {
        return NULL;
    }
    adptArray->size = 0;
    adptArray->copyFunc = copyFunc;
    adptArray->delFunc = delFunc;
    adptArray->printFunc = printFunc;
    adptArray->elements =NULL;
    
    return adptArray;
}

// return the size of the array
int GetAdptArraySize(PAdptArray array) {
    if (array == NULL) {
        return FAIL;
    }
    return array->size;
}

// return copy of the value of an element in the array
PElement GetAdptArrayAt(PAdptArray array, int index) {
    if (array == NULL || index < 0 || index > array->size || NULL ==array->elements [index] || !array) {
        return NULL;
    }
    return array->copyFunc(array->elements[index]);
}

//delete the array and free the memory
void DeleteAdptArray(PAdptArray array) {
    if (array == NULL) {
        return;
    }
    //delete every element by del_function then free the memory of elements and the array
    
    for (int i = 0; i < array->size; i++) {
    	if(array->elements[i] != NULL){ 
        array->delFunc(array->elements[i]);
        }
    }
    free(array->elements);
    free(array);
}

//set the array element by index  if the index bigger then the size of array we make array bigger index+1
Result SetAdptArrayAt(PAdptArray array, int index, PElement element) {
    if (array == NULL || index < 0) {
        return FAIL;
    }
    if (index > array->size) {
        PElement* new_elements = (PElement*)realloc(array->elements, (index + 1) * sizeof(PElement));
        // if realloc dont work free element and return false
        if (new_elements == NULL) {
            return FAIL;
        }
        
        // move all the elements from the end of the last give them all null until we are at the index
        for (int i = array->size; i < (index+1); i++) {
            new_elements[i] = NULL;
        }
        //update the size of the array
        array->size = index + 1;
        array->elements = new_elements;
        
    }
	// if the elemnts exist we delete him
  	if(array->elements[index]){
  	array->delFunc(array->elements[index]);
  	}

	array->elements[index] = array->copyFunc(element);
	
    return SUCCESS;
}

//print the array by moving all the elements.
void PrintDB(PAdptArray array) {

    // if the array is null return nothing
    if (array == NULL) {
        return;
    }

    //if the element[i] is not none we use print function to run it. 
    for (int i = 0; i < array->size; i++) {
        if(array->elements[i]) {
            array->printFunc(array->elements[i]);
        }

    }
}
