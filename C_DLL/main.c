#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int main() {
    struct doubly_linked_list_t *dll1, *dll2;
    dll1 = dll_create();
    if(dll1==NULL){
        printf("Failed to allocate memory");
        return 8;
    }
    dll2 = dll_create();
    if(dll2==NULL){
        printf("Failed to allocate memory");
        free(dll1);
        return 8;
    }
    int res, to_add=0, op;

    printf("Enter first list: ");
    while (1){
        res = scanf("%d", &to_add);
        if(res!=1){
            printf("Incorrect input");
            dll_clear(dll1);
            dll_clear(dll2);
            free(dll1);
            free(dll2);
            return 1;
        }
        if(to_add==-1) break;
        res = dll_push_back(dll1, to_add);
        if(res==2){
            printf("Failed to allocate memory");
            dll_clear(dll1);
            dll_clear(dll2);
            free(dll1);
            free(dll2);
            return 8;
        }
    }
    to_add = 0;
    printf("Enter second list: ");
    while (1){
        res = scanf("%d", &to_add);
        if(res!=1){
            printf("Incorrect input");
            dll_clear(dll1);
            dll_clear(dll2);
            free(dll1);
            free(dll2);
            return 1;
        }
        if(to_add==-1) break;
        res = dll_push_back(dll2, to_add);
        if(res==2){
            printf("Failed to allocate memory");
            dll_clear(dll1);
            dll_clear(dll2);
            free(dll1);
            free(dll2);
            return 8;
        }
    }
    if(dll_is_empty(dll1) && dll_is_empty(dll2)){
        printf("Not enough data available");
        free(dll1);
        free(dll2);
        return 3;
    }
    printf("Choose method: ");
    res = scanf("%d", &op);
    if(res!=1){
        printf("Incorrect input");
        dll_clear(dll1);
        dll_clear(dll2);
        free(dll1);
        free(dll2);
        return 1;
    }
    switch (op) {
        case 0:
            dll_concat_zip(dll1, dll2);
            break;
        case 1:
            dll_concat_begin(dll1, dll2);
            break;
        case 2:
            dll_concat_end(dll1, dll2);
            break;
        default:
            printf("Incorrect input data");
            dll_clear(dll1);
            dll_clear(dll2);
            free(dll1);
            free(dll2);
            return 2;
    }
    dll_display(dll1);
    printf("\n");
    dll_display_reverse(dll1);
    dll_clear(dll1);
    dll_clear(dll2);
    free(dll1);
    free(dll2);
    return 0;
}
