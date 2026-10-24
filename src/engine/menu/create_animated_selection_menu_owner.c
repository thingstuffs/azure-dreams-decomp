#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"

#include "common.h"
#include "engine/menu.h"

typedef struct S_8004F5F4_sub {
    u8 pad0[0x4];
    void *result;
} S_8004F5F4_sub;

typedef struct S_8004F5F4_node {
    u8 pad0[0x10];
    void (*callback)(void *self);
    u8 pad14[0x1E - 0x14];
    u16 flags;
    S_8004F5F4_sub sub;
} S_8004F5F4_node;

/* Creates a callback node and initializes its result, marking failure if initialization fails. */
void *create_animated_selection_menu_owner(void *unused, void *source)
{
    S_8004F5F4_node *node = allocate_flagged_object_node(0);
    void *result;
    S_8004F5F4_sub *sub;
    s32 global_flags;
    u8 *global_page;

    if (node != 0) {
        node->callback = handle_animated_selection_menu_cancel;
        sub = &node->sub;
        result = (sub->result = create_animated_selection_menu(source));
        if (result == 0) {
            do {
                node->flags |= 0x8000;
            } while (0);
            global_flags = object_flag_block.flags;
            node = 0;
            global_flags |= 0x8000;

            global_page = (u8 *)0x80080000;

            *(s32 *)(global_page + 0x14A0) = global_flags;
        }
    }
    return node;
}
