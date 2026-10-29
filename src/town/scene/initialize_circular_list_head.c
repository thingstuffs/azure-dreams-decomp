#include "common.h"
#include "sdk/libc.h"
#include "town/scene.h"

extern void *town_actor_control[];

/* Clear the list head record and link it to itself. */
void initialize_circular_list_head(void) {
    void **head_link = town_actor_control;
    void *head = head_link;

    memset(head, 0, 0x4C);
    *head_link = head;
    head_link[1] = head;
}
