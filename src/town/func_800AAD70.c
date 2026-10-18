#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif


extern s32 scale_random_to_unsigned_halfword_limit();
struct Dst;
struct Elem;
void func_8003DB94(struct Dst *state, struct Elem *entries, short index);
extern s32 func_8004491C();
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
void fade_timed_primitive(void *record_fields, void *unused, Rec_D_80082E80 *primitive);
extern s32 D_800D1464;

typedef struct S_800A84D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800A84D0_0;


   /* arg0 in create_randomized_position_effect */

typedef struct S_800A84D0_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800A84D0_3;

typedef struct S_800A84D0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800A84D0_4;

/* Creates an effect at the supplied position and initializes its sprite and random state. */
void *create_randomized_position_effect(MovingPosition *source_position) {
    s32 random_offset;
    S_800A84D0_3 *sprite;
    MovingPosition *position;
    void *object;
    S_800A84D0_4 *effect_state;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        position = ((S_800A84D0_0 *)object)->unk_08;
        sprite = ((S_800A84D0_0 *)object)->unk_0C;
        ((S_800A84D0_0 *)object)->unk_10 = &fade_timed_primitive;
        func_8004491C(object, func_80045340);
        position->unk_02 = (u16) source_position->unk_02;
        position->unk_06 = (u16) source_position->unk_06;
        position->unk_0A = (u16) source_position->unk_0A;
        func_8003DB94(sprite, &D_800D1464, 0);
        sprite->unk_0E = 0xFF;
        sprite->unk_0D = 0xFF;
        sprite->unk_0C = 0xFF;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_10 = 0x60;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        random_offset = scale_random_to_unsigned_halfword_limit(7);
        effect_state = object + 0x20;
        effect_state->unk_02 = (s16) (random_offset + scale_random_to_unsigned_halfword_limit(7));
    }
    return object;
}

/* MECHANISM: Preserve the seed's 0x28 frame and s3/s2/s1/s0 held-value layout.
   Unsigned byte stores force li 0x00ff at word 33; signed s8 had emitted li -1. */
