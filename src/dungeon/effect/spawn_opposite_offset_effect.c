#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800B653C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B653C_0;

typedef struct S_800B653C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800B653C_1;   /* held_arg0 in spawn_opposite_offset_effect */

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

extern s32 register_node();
extern s32 rand();
extern s32 func_8003DB94();

extern s32 D_800B63A8;
extern s32 D_800DEA68;

/* Spawn an offset effect with randomized motion opposite to the source. */
void spawn_opposite_offset_effect(void *source_data, u32 direction_bits) {
    S_800B653C_1 *source;
    s16 *y_offset;
    s16 *x_offsets;
    u32 direction;
    SpriteFrameState *sprite;
    S_800B653C_0 *motion;
    SubObject *effect_params;
    Object *effect;

    source = source_data;
    direction_bits >>= 9;
    direction = direction_bits & 7;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        motion = effect->unk8;
        sprite = effect->unkC;
        effect_params = &effect->sub20;
        effect->unk10 = &D_800B63A8;
        register_node(effect, project_sprite_chain);
        x_offsets = dir_step_x;
        y_offset = &dir_step_y[direction];
        motion->unk_02 =
            (s16)(source->unk_02 -
                  (x_offsets[direction] * 0x10));
        motion->unk_06 =
            (s16)(source->unk_06 - (*y_offset * 0x10));
        motion->unk_0A = source->unk_0A;
        motion->unk_0C =
            0 - (source->unk_0C * ((rand() & 1) + 2));
        motion->unk_10 =
            0 - (source->unk_10 * ((rand() & 1) + 2));
        motion->unk_14 = (~rand() & 1) << 0xF;
        func_8003DB94(sprite, &D_800DEA68, 0);
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->tpage_abr = 0x60;
        sprite->flags |= 0xC;
        effect_params->unk18 = 0x10;
        effect_params->unk16 = 0x10;
        effect_params->unk14 = 0x10;
        effect_params->unkE = (rand() & 3) | 4;
        effect_params->unk8 = 0x800;
    }
}
