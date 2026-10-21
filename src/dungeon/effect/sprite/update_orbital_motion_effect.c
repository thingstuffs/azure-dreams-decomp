#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818BD3B0_0_pre {
    u16 unk_00;
} S_818BD3B0_0_pre;   /* the 0x2 bytes before arg0 in update_orbital_motion_effect, addressed as arg0[-1] */

typedef struct S_818BD3B0_0 {
    void * unk_00;
    u16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    u16 unk_0C;
} S_818BD3B0_0;   /* arg0 in update_orbital_motion_effect */

typedef struct S_818BD3B0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BD3B0_1;

typedef struct S_818BD3B0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BD3B0_2;   /* arg1 in update_orbital_motion_effect */

s32 select_record_entry_and_value();
s32 advance_sprite_animation_and_textures();
s32 func_800644B8();
s32 func_80064584();
extern M2C_UNK D_800DEC70[3];

/* Advance orbital motion, expire it at its duration, and update the object. */
void update_orbital_motion_effect(void *motion, S_818BD3B0_2 *position, SpriteFrameState *object) {
    s16 angle;
    s32 radius_product;
    s32 height_offset;
    u16 tick;
    S_818BD3B0_1 *owner;

    owner = ((S_818BD3B0_0 *)motion)->unk_00;
    owner->unk_14 = (u16) (owner->unk_14 + 1);
    tick = ((S_818BD3B0_0 *)motion)->unk_04 + 1;
    ((S_818BD3B0_0 *)motion)->unk_04 = tick;
    if (((S_818BD3B0_0 *)motion)->unk_06 < (s16) tick) {
        ((S_818BD3B0_0_pre *)motion)[-1].unk_00 = (u16) (((S_818BD3B0_0_pre *)motion)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
        return;
    }
    height_offset = (s32) ((func_80064584((s16) tick << 7) >> 4) * ((S_818BD3B0_0 *)motion)->unk_0A) >> 8;
    ((S_818BD3B0_0 *)motion)->unk_08 = (s16) height_offset;
    position->unk_08 = (s32) (position->unk_14 - (height_offset << 0x10));
    radius_product = (func_800644B8((s16) ((S_818BD3B0_0 *)motion)->unk_04 << 7) >> 4) * ((S_818BD3B0_0 *)motion)->unk_0A;
    angle = ((S_818BD3B0_0 *)motion)->unk_0C + 0x80;
    ((S_818BD3B0_0 *)motion)->unk_0C = (u16) angle;
    ((S_818BD3B0_0 *)motion)->unk_08 = (s16) (radius_product >> 8);
    position->unk_00 = (s32) (position->unk_0C + (((func_80064584(angle) >> 4) * ((S_818BD3B0_0 *)motion)->unk_08) << 8));
    position->unk_04 = (s32) (position->unk_10 + (((func_800644B8((s16) ((S_818BD3B0_0 *)motion)->unk_0C) >> 4) * ((S_818BD3B0_0 *)motion)->unk_08) << 8));
    advance_sprite_animation_and_textures(object);
    if (object->flags & 0x6000) {
        select_record_entry_and_value(object, &D_800DEC70, 0);
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame and s0/s2/s1 lifetime shape. */
