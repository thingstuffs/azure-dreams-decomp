#include "common.h"
#include "shared/object_flags.h"

typedef struct Inner {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[2];
    u16 fieldA;
    s32 fieldC;
} Inner;

typedef struct Outer {
    u8 pad0[8];
    Inner *inner8;
    Inner *innerC;
    u8 pad10[0xE];
    u16 flags1E;
} Outer;

extern u16 sprite_effect_update_count[];

/* Copies a linked object's coordinates and color, or removes the effect when the linked object is
   marked for deletion. */
void process_effect_record(void *ptr, Inner *fields_target, Inner *field_c_target)
{
    Outer *outer;
    Inner *inner;
    s32 flags1E;

    outer = *(Outer **)((u8 *)ptr + 8);
    flags1E = outer->flags1E & 0x8000;
    sprite_effect_update_count[0]++;
    if (flags1E != 0) {
        ((u16 *)ptr)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    field_c_target->fieldC = outer->innerC->fieldC;
    inner = (*(Outer **)((u8 *)ptr + 8))->inner8;
    fields_target->field2 = inner->field2;
    fields_target->field6 = inner->field6;
    fields_target->fieldA = inner->fieldA;
}
