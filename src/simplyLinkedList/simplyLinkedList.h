
/*
Copyright (C) 2023 Efraileg (Eduardo Fraile González)
Obviously values like structures are not allowed due to some functions need a special comparator to them but it can be implemented if it is necessary.
*/

typedef double typeData;

#define CASTING_TYPEDATA_PTR(value) (*((typeData*)(value)))    // Expected value as pointer like void*/float*/int*
#define CASTING_VOID_PTR(value) ((void*)(value))               // Expected value as pointer like float*/int*/double* 

// This structure includes the value to store and a pointer to next node.
struct Node{
    void* value;                  // This is a pointer to any data type.
    struct Node* next_node;       // This store the address of the next node. 
};

// This structure includes the pointer that runs through the linked list and a counter of its elements.
struct LinkedList{
    struct Node* head;            // This is the pointer of the linked list, it points to the current element of the list, the first initially.
    __uint64_t cont_elements;     // This counts the number of elements of the linked list.
};

char is_empty(struct LinkedList* linked_list)
{
    return (!linked_list || linked_list->head == NULL);
}

char in_end(struct LinkedList* linked_list)
{
    return (linked_list && linked_list->head) ? (linked_list->head->next_node == NULL) : 0;
}

/*void next(struct LinkedList linked_list){

    if(!linked_list || linked_list->head == NULL) return;

    linked_list->head = linked_list->head->next_node;
}*/

void* current_value(struct LinkedList* linked_list)
{    
    return (linked_list && linked_list->head) ? linked_list->head->value : NULL;
}

void insert_value(struct LinkedList* linked_list, void* value){

    struct Node* n = malloc(sizeof(struct Node));

    n -> value = value;
    n -> next_node = NULL;

    if(is_empty(linked_list)){
        linked_list->head = n;
        linked_list->cont_elements++;
        return;
    }

    struct Node* aux_ptr = linked_list->head;
    
    while(aux_ptr->next_node != NULL){
        aux_ptr = aux_ptr->next_node;
    }

    aux_ptr->next_node = n;
    linked_list->cont_elements++;
}

void erase_first(struct LinkedList* linked_list){

    if(!linked_list || is_empty(linked_list)) return;

    struct Node* current_head = linked_list->head;
    linked_list->head = linked_list->head->next_node;
    
    free(current_head);
    linked_list->cont_elements--;
}

void erase_last(struct LinkedList* linked_list){

    if(!linked_list || is_empty(linked_list)) return;

    struct Node* current_pointer  = linked_list->head;
    struct Node* previous_pointer = linked_list->head;

    while(current_pointer->next_node != NULL){
        previous_pointer = current_pointer;                     // The previous node.
        current_pointer = current_pointer->next_node;           // The current node.
    }

    if(previous_pointer) previous_pointer->next_node = NULL;    // The penultimate next_node pointer is set to NULL.

    free(current_pointer);                                      // The current pointer is erased.
    linked_list->cont_elements--;
}

void erase_element(struct LinkedList* linked_list, typeData* value){

    if(!linked_list || is_empty(linked_list)) return;

    struct Node* current_pointer = linked_list->head;
    struct Node* previous_pointer = linked_list->head;

    while(current_pointer){
        
        if((*(typeData*)(current_pointer->value)) == *value) break;   // If the value has been founded we leave the loop.

        previous_pointer = current_pointer;                           // As long as the value is not found the pointers will be updated.
        current_pointer = current_pointer->next_node;
    }

    if(current_pointer == linked_list->head){           // The value to erase is the first in the linked list. 
        erase_first(linked_list);
        return;
    }

    if(current_pointer->next_node == NULL){             // The value to erase is the last in the linked list.
        erase_last(linked_list);
        return;
    }
            
    // The value to erase isn't the first and isn't the last.
    previous_pointer->next_node = current_pointer->next_node;       // The previous pointer points to the next of the current pointer.
    free(current_pointer);
    linked_list->cont_elements--;
}
