#include "common.h"
#include "slus/spadstk.h"

extern void draw_tinted_node_sprites(void *a0, void *a1);

/* Calls draw_tinted_node_sprites on a temporary scratchpad stack (SDK SetSpadStack/ResetSpadStack), restores the original stack, and returns zero. */
int draw_tinted_node_sprites_scratch(void *forwarded_ptr, int unused_arg, void *second_ptr)
{
    SetSpadStack(SPAD_STACK_ADDR);
    draw_tinted_node_sprites(forwarded_ptr, second_ptr);
    ResetSpadStack();
    return 0;
}
