#include "common.h"

extern void *D_800FE490[];

/* Sets the first two pointers in D_800FE490 to the array itself. */
void initialize_pointer_table_self_links(void) {
    D_800FE490[0] = D_800FE490;
    D_800FE490[1] = D_800FE490;
}
