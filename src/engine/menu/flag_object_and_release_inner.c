#include "common.h"
#include "shared/object_flags.h"

#include "common.h"

typedef struct InnerA464 {
    u8 pad0[0x8];
    s32 field_8;
    u8 padC[0x18 - 0xC];
    s32 field_18;
} InnerA464;

typedef struct ObjA464 {
    u8 pad0[0x1E];
    u16 flags;
    InnerA464 inner;
} ObjA464;

extern void mark_object_removal_for_inner_release(s32 object);
extern s32 D_800814A0_store;

/* Sets object and global flags and processes the object's two inner values. */
void flag_object_and_release_inner(ObjA464 *obj)
{
    InnerA464 *inner;

    if (obj != 0) {
        obj->flags |= 0x8000;
        inner = &obj->inner;
        D_800814A0_store = object_flag_block.flags | 0x8000;
        mark_object_removal_for_inner_release(inner->field_8);
        mark_object_removal_for_inner_release(inner->field_18);
    }
}
