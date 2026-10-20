#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

typedef struct {
    s32 words[6];
} Copy24;

extern s32 D_80175F38;

s32 resolve_record_orientation_or_fallback(s32, void *, s16 *, s32);
void select_sprite_entry(void *, s32, s32);
void func_800478B8(void *);

typedef struct S_80174D24_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    Copy24 * unk_04;
    void * unk_08;
} S_80174D24_0;   /* arg0 in advance_timed_target_flags */

typedef struct S_80174D24_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174D24_1;   /* arg1 in advance_timed_target_flags */

typedef struct S_80174D24_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174D24_2;   /* object in advance_timed_target_flags */

typedef struct S_80174D24_4 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_80174D24_4;   /* ((S_80174D24_0 *)arg0)->unk_08 in advance_timed_target_flags */

/* Copies object data with offsets and advances a timed target flag cycle. */
void advance_timed_target_flags(void *state, void *output, void *target)
{
    u16 offsets[3];
    void *object;
    Copy24 *source;
    s32 copy_word_a;
    s32 copy_word_b;
    s32 offset_mode;
    s32 object_id;
    s32 phase;
    u16 old_ticks;
    s32 signed_ticks;
    u16 target_flags;

    if (((S_80174D24_4 *)(((S_80174D24_0 *)state)->unk_08))->unk_2C != &D_80175F38) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    source = ((S_80174D24_0 *)state)->unk_04;
    *(Copy24 *)output = *source;

    object = ((S_80174D24_0 *)state)->unk_08;
    offset_mode = 0;
    object_id = ((S_80174D24_2 *)object)->unk_08;
    if (resolve_record_orientation_or_fallback(object_id, object,
                      (s16 *)offsets, offset_mode) != 0) {
        ((S_80174D24_1 *)output)->unk_00.at02.v += offsets[0];
        ((S_80174D24_1 *)output)->unk_04.at02.v += offsets[1];
        ((S_80174D24_1 *)output)->unk_08.at02.v += offsets[2];
    }

    old_ticks = ((S_80174D24_0 *)state)->unk_02;
    phase = ((S_80174D24_0 *)state)->unk_00.s;
    copy_word_a = old_ticks + 1;
    ((S_80174D24_0 *)state)->unk_02 = copy_word_a;

    switch (phase) {
    case 0:
        func_800478B8(target);
        target_flags = ((SpriteFrameState *)target)->flags;
        if ((target_flags & 0x6000) == 0) {
            return;
        }
        ((SpriteFrameState *)target)->flags = target_flags | 0x80;
        ((S_80174D24_0 *)state)->unk_02 = 0;
        ((S_80174D24_0 *)state)->unk_00.u++;
        break;
    case 1:
        signed_ticks = (s16)copy_word_a;
        if (signed_ticks < 0x40) {
            return;
        }
        ((SpriteFrameState *)target)->flags &= 0xFF7F;
        select_sprite_entry(target, 0x38, 0);
        ((S_80174D24_0 *)state)->unk_02 = 0;
        ((S_80174D24_0 *)state)->unk_00.s = 0;
        break;
    }
}

/* MECHANISM: True-space epilogue joins and a u16[3] output object produce the 0x28 frame. Ordering
   mode_zero before mode_one removes the word-61 displacement cascade. */
