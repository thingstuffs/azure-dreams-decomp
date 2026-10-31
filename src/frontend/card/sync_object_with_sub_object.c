#include "common.h"
#include "shared/object_flags.h"
#include "frontend/settings.h"

/* Updates object flags and display offset from its linked sub-object. */
void sync_object_with_sub_object(SettingsSyncObjectBody *object)
{
    SettingsSyncChildObjectBody *sub_object = object->child;
    u16 *prior_flags = (u16 *)((u8 *)object - 2);

    if (sub_object->kind == 4) {
        object->flags &= 0xFFFD;
    }
    if (object->state == 0) {
        object->position_delta = (sub_object->position_value * 0x10) + 0xA0;
        if (sub_object->flags & 1) {
            *prior_flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
