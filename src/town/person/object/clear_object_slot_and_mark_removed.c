#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in clear_object_slot_and_mark_removed, addressed as arg0[-1] */


/* Clears the object slot and sets the object and global removal flags. */
void clear_object_slot_and_mark_removed(void *object) {
    s32 slot_offset;
    u8 *slots;

    slots = object_index_slots;
    slot_offset = ((Rec_func_80094268_arg0 *)object)->unk_60 * 8;
    (*(s32 *)((u8 *)(slots + slot_offset) + 4)) = 0;
    (*(u16 *)((u8 *)object + -2)) = (u16) (((ObjectStatusPrefix16 *)object)[-1].unk_00 | 0x8000);
    object_flag_block.flags |= 0x8000;
}
