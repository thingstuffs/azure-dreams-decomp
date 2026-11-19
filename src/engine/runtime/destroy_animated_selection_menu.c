#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "engine/runtime.h"

/* Canonical global flags word shared by several sibling functions in this
 * TU family (code9.c, code10.c, code11.c, code5.c, w_8004F558.c, ...).
 * w_8004F558.c (same D_800814A0 |= 0x8000 tail as this function) declares
 * it as a plain `extern int` and matches with the address recomputed
 * TWICE (load then store, in different registers) -- follow that. */
extern int D_800814A0;

extern void func_8001832C(AnimatedSelectionEntry *entry);

/* Process a non-null entity's nonzero handles and set its flags and the global flags to include 0x8000. */
void destroy_animated_selection_menu(ObjectNodeHeader *entity)
{
    s32 handle_index;
    AnimatedSelectionEntry **entry;

    if (entity != 0) {
        handle_index = 0;
        entry = NODE_BODY(entity);
        for (; handle_index < 3; handle_index++) {
            if (entry[1] != 0) {
                func_8001832C(entry[1]);
            }
            entry++;
        }
        entity->flags |= 0x8000;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
