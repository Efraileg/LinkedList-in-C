/*
Copyright (C) 2023 Efraileg (Eduardo Fraile González)

This is a simple test file to prove the library with different values. 
Obviously values like structures are not allowed due to some functions need a special comparator to them but it can be implemented if it is necessary.
*/

#include <stdio.h>
#include <stdlib.h>
#include "doubleLinkedList.h"

int main(void){

    struct doubleLinkedList linked_list;
    reset_list(&linked_list);

    typeData* value = NULL;

    for(typeData i=1; i<=10; i++){
        value = malloc(sizeof(typeData));       // Every iteration is allocated a new space in memory to avoid modify the others elements. 
        *value = i;
        insert_element(&linked_list, value);
    }

    erase_first(&linked_list);
    erase_last(&linked_list);
    
    value = malloc(sizeof(typeData));           // Another allocated space in memory instead of the last allocated space memory.
    *value = 6;
    erase_element(&linked_list, value);

    /////////////////////////////////////////

    value = malloc(sizeof(typeData));
    *value = 3;
    
    printf("Number of nodes: %lu\n", linked_list.n_nodes);
    printf("Value %d is founded: %d\n", *value, is_in(&linked_list, value));

    to_begin(&linked_list);
    while(!in_end(&linked_list)){

        printf("Value: %d\n", *((typeData*)get_value(&linked_list)));
        next(&linked_list);
    }

    if(valid_access_linkedList(&linked_list)){
        printf("Value: %d\n", *((typeData*)get_value(&linked_list)));
    }

    erase_all(&linked_list);
    return 0;
}
