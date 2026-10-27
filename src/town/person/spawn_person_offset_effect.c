#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "sdk/libc.h"
#include "town/person/effects.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800ABC00_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800ABC00_1;   /* held_arg0 in spawn_person_offset_effect */

typedef struct S_800ABC00_3 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800ABC00_3;

typedef struct {
    u8 pad0[8];
    s32 unk8;
    u8 padC[2];
    s16 unkE;
    u8 pad10[4];
    s16 unk14;
    s16 unk16;
    s16 unk18;
    u8 pad1A[6];
} SubObject;

typedef struct {
    u8 pad0[8];
    void *unk8;
    void *unkC;
    void *unk10;
    u8 pad14[12];
    SubObject sub20;
} Object;

extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern void select_record_entry_and_value(void *state, void *entries, short index);

extern s32 town_radial_offset_callback;
extern s32 radial_sprite_entries;

/* Spawns an offset effect with randomized motion opposite the source velocity. */
void spawn_person_offset_effect(void *source_data, u32 angle)
{
    S_800ABC00_1 *source;
    s16 *y_step;
    s16 *x_steps;
    u32 direction;
    SpriteFrameState *sprite;
    ObjectPosition *motion;
    SubObject *effect_state;
    Object *effect;

    source = source_data;
    angle >>= 9;
    direction = angle & 7;
    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        motion = effect->unk8;
        sprite = effect->unkC;
        effect_state = &effect->sub20;
        effect->unk10 = &town_radial_offset_callback;
        register_node(effect, project_sprite_chain);
        x_steps = dir_step_x;
        y_step = &dir_step_y[direction];
        motion->x.w.i =
            (s16)(source->unk_02 -
                  (x_steps[direction] * 0x10));
        motion->y.w.i =
            (s16)(source->unk_06 - (*y_step * 0x10));
        motion->z.w.i = source->unk_0A;
        motion->velocity_x =
            0 - (source->unk_0C *
                 ((rand() & 1) + 2));
        motion->velocity_y =
            0 - (source->unk_10 *
                 ((rand() & 1) + 2));
        motion->velocity_z = (~rand() & 1) << 0xF;
        select_record_entry_and_value(sprite, &radial_sprite_entries, 0);
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->tpage_abr = 0x60;
        sprite->flags |= 0xC;
        ((S_800ABC00_3 *)effect_state)->unk_02 = (rand() & 3) | 4;
    }
}
