#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

struct doubly_linked_list_t* dll_create(){
    struct doubly_linked_list_t* list = calloc(1, sizeof(struct doubly_linked_list_t));
    if(list==NULL) return NULL;
    list->tail = NULL;
    list->head = NULL;
    return list;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value){
    if(dll==NULL) return 1;
    struct node_t *node = calloc(1, sizeof(struct node_t));
    if(node == NULL) return 2;
    node->data = value;
    if(dll_is_empty(dll)==1){
        dll->head = node;
        dll->tail = node;
        return 0;
    }
    node->prev = dll->tail;
    dll->tail->next = node;
    dll->tail = node;
    return 0;
}

int dll_size(const struct doubly_linked_list_t* dll){
    if(dll==NULL) return -1;
    if(dll_is_empty(dll)==1) return 0;
    int size = 1;
    struct node_t *node = dll->head;
    while (node!=dll->tail){
        size++;
        node = node->next;
    }
    return size;
}
int dll_is_empty(const struct doubly_linked_list_t* dll){
    if(dll==NULL) return -1;
    if(dll->head == NULL && dll->tail==NULL) return 1;
    return 0;
}

void dll_clear(struct doubly_linked_list_t* dll){
    if(dll==NULL || dll_is_empty(dll)) return;
    struct node_t *curr_node = dll->head, *next_node;
    while (curr_node != NULL){
        next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
    }
    dll->head = NULL;
    dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t* dll){
    if(dll==NULL || dll_is_empty(dll)) return;
    struct node_t *node = dll->head;
    while(node!=NULL){
        printf("%d ", node->data);
        node = node->next;
    }
}
void dll_display_reverse(const struct doubly_linked_list_t* dll){
    if(dll==NULL || dll_is_empty(dll)) return;
    struct node_t *node = dll->tail;
    while(node!=NULL){
        printf("%d ", node->data);
        node = node->prev;
    }
}

int dll_concat_zip(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2){
    if(dll1==NULL || dll2==NULL) return 1;
    if(dll_is_empty(dll1)){
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    if(dll_is_empty(dll2)){
        return 0;
    }
    struct node_t *dll1_node = dll1->head, *dll2_node = dll2->head, *next_dll1 = dll1->head->next, *next_dll2 = dll2->head->next;

    while (1){

        if(dll1_node->next==NULL && dll2_node->next == NULL){
            dll1_node->next = dll2_node;
            dll1->tail=dll2_node;
            dll2_node->prev = dll1_node;
            dll2->head = NULL;
            dll2->tail = NULL;
            return 0;
        }
        if(dll1_node->next==NULL){
            dll1_node->next = dll2_node;
            dll1->tail = dll2->tail;
            dll2_node->prev = dll1_node;
            dll2->head = NULL;
            dll2->tail = NULL;
            return 0;
        }
        if(dll2_node->next==NULL){
            dll1_node->next = dll2_node;
            dll2_node->next = next_dll1;
            next_dll1->prev = dll2_node;
            dll2_node->prev = dll1_node;
            dll2->head = NULL;
            dll2->tail = NULL;
            return 0;
        }


        dll1_node->next = dll2_node;
        dll2_node->prev = dll1_node;

        dll2_node->next = next_dll1;
        next_dll1->prev = dll2_node;

        next_dll2->prev = next_dll1;



        //dll1_node->prev =
        dll1_node = next_dll1;
        dll2_node = next_dll2;
        next_dll1 = dll1_node->next;
        next_dll2 = dll2_node->next;

    }

    return 0;
}
int dll_concat_begin(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2){
    if(dll1==NULL || dll2==NULL) return 1;
    if(dll_is_empty(dll2)) return 0;
    if(dll_is_empty(dll1)){
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    //struct node_t *curr_head = dll1->head;
    dll2->tail->next = dll1->head;
    dll1->head->prev = dll2->tail;
    dll1->head = dll2->head;

    dll2->head = NULL;
    dll2->tail = NULL;
    return 0;
}
int dll_concat_end(struct doubly_linked_list_t* dll1, struct doubly_linked_list_t* dll2){
    if(dll1==NULL || dll2==NULL) return 1;
    if(dll_is_empty(dll2)) return 0;
    if(dll_is_empty(dll1)){
        dll1->head = dll2->head;
        dll1->tail = dll2->tail;
        dll2->head = NULL;
        dll2->tail = NULL;
        return 0;
    }
    //struct node_t *curr_head = dll1->head;
    dll1->tail->next = dll2->head;
    dll2->head->prev = dll1->tail;
    dll1->tail = dll2->tail;

    dll2->head = NULL;
    dll2->tail = NULL;
    return 0;
}