#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "engine/menu.h"
#include "engine/runtime.h"

extern int D_800814A0;

/* Recycles the object's data and sets bit 0x8000 in its flags and the global flags. */
void destroy_animated_selection_menu_owner(AnimatedSelectionMenuOwnerBody *object)
{
    unsigned short *flags = &NODE_HEADER(object)->flags;

    destroy_animated_selection_menu(object->result);
    *flags |= NODE_REMOVE;
    D_800814A0 |= OBJECT_REMOVE_PENDING;
}
