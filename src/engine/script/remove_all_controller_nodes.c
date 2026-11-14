#include "common.h"
#include "m2c_compat.h"

#include "engine/node.h"
#include "engine/object.h"
#include "engine/script.h"

/* --- port/hal accessor shims (mechanical, no HAL dependency) --- */
#define U32AT(b, o) (*(u32 *)((u8 *)(b) + (o)))
#define PPTR(v)     ((void *)(u32)(v))
#define PVAL(p)     ((u32)(p))

/*
 * Removes every node from the controller's list and cleans up its owning object.
 *
 * port body: port/hal/resident_gap2.c:353
 */
void remove_all_controller_nodes(void *controller)
{
    u8 *list_head = (u8 *)controller + 8;
    u8 *node = (u8 *)PPTR(U32AT(list_head, 0x08));

    while (node != list_head) {
        u8 *owner = (u8 *)PPTR(U32AT(node, 0x00));
        u8 *object;

        if (U32AT(owner, 0x00) != 0)
            clear_word(PPTR(U32AT(owner, 0x00)));
        unlink_owner_list_node(node);
        object = owner - 32;
        unlink_node(object);
        unlink_active_node(object);
        node = (u8 *)PPTR(U32AT(list_head, 0x08));
    }
}
