#include "common.h"

extern s32 memset();
extern s32 D_800CFCB4;

/* Clear the list head record and link it to itself. */
void initialize_circular_list_head(void) {
    s32 *head_link = &D_800CFCB4;
    void *head = head_link;

    memset(head, 0, 0x4C);
    *head_link = (s32)head;
    *(void **)((u8 *)head + 4) = head;
}
