
/*
Copyright (C) 2023 Efraileg (Eduardo Fraile González)

This is a simple test file to prove the library with different values. 
Obviously values like structures are not allowed due to some functions need a special comparator to them but it can be implemented if it is necessary.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "simplyLinkedList.h"

int main(void){

    struct LinkedList linked_list;
    typeData* value = NULL;

    linked_list.cont_elements = 0;
    linked_list.head = NULL;

    // For this test consider that typeData is intended for primitive type of data like int, float, double due to the values in the loop.
    for(typeData i=1.0; i<=10.0; i++){          
        value = malloc(sizeof(typeData));
        *value = i;
        insert_value(&linked_list, CASTING_VOID_PTR(value));     // Casting to void* is unnecessary.
    }

    erase_first(&linked_list);
    erase_last (&linked_list);

    value = malloc(sizeof(typeData));
    *value = 8.0;
    erase_element(&linked_list, value);

    *value = 7.0;
    erase_element(&linked_list, value);

    printf("\nNum nodes: %lu", linked_list.cont_elements);

    struct Node* aux = linked_list.head;
    
    // aux->next_node != NULL, this is valid but avoid the last node due to its next node is NULL.
    // As long as "aux" isn't NULL we can manipulate it and continue moving through the linked list.
    while(aux != NULL){          
        printf("\nNode: %f", CASTING_TYPEDATA_PTR(aux->value)); // Consider change the type of format considering the type of value.
        aux = aux->next_node;
    }

    printf("\n");
    return 0;
}