#include "common.h"
#include "shared/object_flags.h"
#include "engine/menu.h"
#include "engine/runtime.h"

extern int D_800814A0;

/* Recycles the object's data and sets bit 0x8000 in its flags and the global flags. */
void destroy_animated_selection_menu_owner(AnimatedSelectionMenuOwnerBody *object)
{
    unsigned short *flags = (unsigned short *)((unsigned char *)object - 0x2);

    destroy_animated_selection_menu(object->result);
    *flags |= 0x8000;
    D_800814A0 |= OBJECT_REMOVE_PENDING;
}
