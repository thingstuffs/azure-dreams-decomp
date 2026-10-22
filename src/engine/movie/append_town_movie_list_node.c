#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/movie.h"

/* Appends a node to the end of the linked list. */
void append_list_tail(void *list_head, MovieListNode *new_node) {
    MovieListNode *tail;

    tail = list_head;
    if (tail->next != 0) {
        do {
            tail = tail->next;
        } while (tail->next != 0);
    }
    tail->next = new_node;
    new_node->next = 0;
}
