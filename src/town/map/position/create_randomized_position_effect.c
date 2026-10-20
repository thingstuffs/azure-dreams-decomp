#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 scale_random_to_unsigned_halfword_limit();
struct Dst;
struct Elem;
void func_8003DB94(struct Dst *state, struct Elem *entries, short index);
extern s32 register_node();
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
void fade_timed_primitive(void *record_fields, void *unused, SpriteFrameState *primitive);
extern s32 D_800D1464;

typedef struct S_800A84D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800A84D0_0;

   /* arg0 in create_randomized_position_effect */

typedef struct S_800A84D0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800A84D0_4;

/* Creates an effect at the supplied position and initializes its sprite and random state. */
void *create_randomized_position_effect(MovingPosition *source_position) {
    s32 random_offset;
    SpriteFrameState *sprite;
    MovingPosition *position;
    void *object;
    S_800A84D0_4 *effect_state;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        position = ((S_800A84D0_0 *)object)->unk_08;
        sprite = ((S_800A84D0_0 *)object)->unk_0C;
        ((S_800A84D0_0 *)object)->unk_10 = &fade_timed_primitive;
        register_node(object, project_sprite_chain);
        position->unk_02 = (u16) source_position->unk_02;
        position->unk_06 = (u16) source_position->unk_06;
        position->unk_0A = (u16) source_position->unk_0A;
        func_8003DB94(sprite, &D_800D1464, 0);
        sprite->color.c.b = 0xFF;
        sprite->color.c.g = 0xFF;
        sprite->color.c.r = 0xFF;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->tpage_abr = 0x60;
        sprite->flags = (u16) (sprite->flags | 0xC);
        random_offset = scale_random_to_unsigned_halfword_limit(7);
        effect_state = object + 0x20;
        effect_state->unk_02 = (s16) (random_offset + scale_random_to_unsigned_halfword_limit(7));
    }
    return object;
}

/* MECHANISM: Preserve the seed's 0x28 frame and s3/s2/s1/s0 held-value layout.
   Unsigned byte stores force li 0x00ff at word 33; signed s8 had emitted li -1. */
