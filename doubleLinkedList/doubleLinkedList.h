
/*
Copyright (C) 2023 Efraileg (Eduardo Fraile González)
 
Obviously values like structures are not allowed due to some functions need a special comparator to them but it can be implemented if it is necessary.
*/

typedef int typeData;

struct Node{

    struct Node* next_node;
    struct Node* previous_node;
    
    void* value_node;
};

struct doubleLinkedList{

    struct Node* head;
    struct Node* tail;
    struct Node* current_node;

    __uint64_t n_nodes;
};

char is_empty(struct doubleLinkedList* linked_list)
{
    return (linked_list) ? (!linked_list->head || !linked_list->tail) : 0;
}

char valid_access_linkedList(struct doubleLinkedList* linked_list)
{
    return (linked_list && !is_empty(linked_list));
}

void next(struct doubleLinkedList* linked_list){
    if(!linked_list || !linked_list->current_node) return;

    linked_list->current_node = linked_list->current_node->next_node;
}

void back(struct doubleLinkedList* linked_list){
    if(!linked_list || !linked_list->current_node) return;

    linked_list->current_node = linked_list->current_node->previous_node;
}

void to_begin(struct doubleLinkedList* linked_list){
    if(!linked_list) return;

    linked_list->current_node = linked_list->head;
}

void to_end(struct doubleLinkedList* linked_list){

    if(!linked_list) return;

    linked_list->current_node = linked_list->tail;
}

char in_begin(struct doubleLinkedList* linked_list)
{
    return (linked_list) ? (linked_list->current_node == linked_list->head) : 0;
}

char in_end(struct doubleLinkedList* linked_list)
{
    return (linked_list) ? (linked_list->current_node == linked_list->tail) : 0;
}

void* get_value(struct doubleLinkedList* linked_list)
{
    return (linked_list && linked_list->current_node) ? (linked_list->current_node->value_node) : NULL;
}

void reset_list(struct doubleLinkedList* linked_list)
{
    linked_list -> current_node = NULL;
    linked_list -> head = NULL;
    linked_list -> tail = NULL;
    linked_list -> n_nodes = 0;
}

void insert_element(struct doubleLinkedList* linked_list, void* value){

    if(!linked_list) return;

    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->value_node = value;
    new_node->next_node = NULL;
    new_node->previous_node = NULL;

    if(is_empty(linked_list)){
        linked_list->head = new_node;
        linked_list->tail = new_node;
        linked_list->current_node = new_node;
        
        linked_list->n_nodes++;
        return;
    }

    //new_node->next_node = NULL;                          // It's innecesary do this again but it's clearer to understand.
    new_node->previous_node = linked_list->current_node;   // The pointer to the previous node of the new node is updated to the current node.
    linked_list->current_node->next_node = new_node;       // The pointer to the next node of the current node is updated to the new node.

    linked_list->tail = new_node;                          // The pointer to the tail is updated to the new node.
    linked_list->current_node = new_node;                  // The pointer to the current node is updated to the new node.
    
    linked_list->n_nodes++;
}

void erase_first(struct doubleLinkedList* linked_list){

    if(!valid_access_linkedList(linked_list)) return;

    // If there is only one element
    if(!linked_list->head->next_node){      // The head is always pointing to the begin, if its next node is NULL there is only one element.
        reset_list(linked_list);
        return;
    }

    // If there are two or more
    struct Node* aux = linked_list->head;                       // Store a copy of the address of the head before losing it.

    // The current node will be updated if is in the begin to guarantee a valid access memory.
    if(in_begin(linked_list)){
        linked_list->current_node = linked_list->head->next_node;   // The current node is updated to the next of the head.
    }

    linked_list->head->next_node->previous_node = NULL;         // The previous node of the next node is updated.  
    linked_list->head = linked_list->head->next_node;           // The head is updated to its next.
    
    linked_list->n_nodes--;
    free(aux);                                                  // Free the allocated memory of the node to be erased.
}

void erase_last(struct doubleLinkedList* linked_list){

    if(!valid_access_linkedList(linked_list)) return;

    // If there is only one element
    if(!linked_list->head->next_node){      // The head is always pointing to the begin, if its next node is NULL there is only one element.
        reset_list(linked_list);
        return;
    }

    struct Node* aux = linked_list->tail;           // Store a copy of the address of the tail before losing it.

    // The current node will be updated if is in the end to guarantee a valid access memory.
    if(in_end(linked_list)){
        linked_list->current_node = linked_list->tail->previous_node;    // The current node is updated to the previous of the tail.
    }

    linked_list->tail->previous_node->next_node = NULL;
    linked_list->tail = linked_list->tail->previous_node;

    linked_list->n_nodes--;
    free(aux);                                      // Free the allocated memory of the node to be erased.
}

void erase_element(struct doubleLinkedList* linked_list, void* value){

    if(!valid_access_linkedList(linked_list)) return;

    to_begin(linked_list);

    while(!in_end(linked_list)){
        
        if(*((typeData*)get_value(linked_list)) != *((typeData*)value)){
            next(linked_list);
            continue;
        }

        break;          // If the value has been founded the loop stop.
    }

    // Erase in the begin of the list.
    if(in_begin(linked_list)){
        erase_first(linked_list); 
        return;
    }

    // Erase in the end of the list.
    if(in_end(linked_list)){
        erase_last(linked_list);
        return;
    }

    // Erase in the middle of the list.
    struct Node* aux = linked_list->current_node;

    linked_list->current_node->previous_node->next_node = linked_list->current_node->next_node;     // Update to the new next node.
    linked_list->current_node->next_node->previous_node = linked_list->current_node->previous_node; // Update to the new previous node.
    linked_list->current_node = linked_list->current_node->next_node;

    linked_list->n_nodes--;
    free(aux);
}

char is_in(struct doubleLinkedList* linked_list, void* value){

    if(!valid_access_linkedList(linked_list)) return 0;

    to_begin(linked_list);
    while(!in_end(linked_list)){

        if(*((typeData*)get_value(linked_list)) != *((typeData*)value)){

            next(linked_list);
            continue;
        }

        to_begin(linked_list);
        return 1;
    }

    to_begin(linked_list);
    return 0;
}

void erase_all(struct doubleLinkedList* linked_list){
    
    if(!valid_access_linkedList(linked_list)) return;

    struct Node* aux = NULL;
    while(!in_end(linked_list)){

        aux = linked_list->current_node;
        next(linked_list);
        free(aux);
    }

    if(valid_access_linkedList(linked_list)) free(linked_list->current_node);
    
    reset_list(linked_list);
}
