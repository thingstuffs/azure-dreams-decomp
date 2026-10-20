#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 scale_random_to_unsigned_halfword_limit();
struct Dst;
struct Elem;
void func_8003DB94(struct Dst *state, struct Elem *entries, short index);
extern s32 register_node();
extern s32 rand();
extern s32 D_800ABB20;
extern s32 D_800D1464;

typedef struct S_8009792C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_8009792C_0;

typedef struct S_8009792C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009792C_1;

typedef struct S_8009792C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_8009792C_2;   /* arg0 in create_randomized_offset_effect */

/* Creates an offset effect with randomized motion and initializes its appearance. */
void *create_randomized_offset_effect(S_8009792C_2 *source, u32 angle) {
    u32 direction;
    SpriteFrameState *appearance;
    S_8009792C_1 *motion;
    void *effect;
    s16 *effect_params;

    angle >>= 9;
    direction = angle & 7;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect_params = (s16 *)((s8 *)effect + 0x20);
        motion = ((S_8009792C_0 *)effect)->unk_08;
        appearance = ((S_8009792C_0 *)effect)->unk_0C;
        ((S_8009792C_0 *)effect)->unk_10 = (s32 *)&D_800ABB20;
        register_node(effect, project_sprite_chain);
        motion->unk_02 = source->unk_02 - dir_step_x[direction] * 0x10;
        motion->unk_06 = source->unk_06 - dir_step_y[direction] * 0x10;
        motion->unk_0A = source->unk_0A;
        motion->unk_0C = -(source->unk_0C * ((rand() & 1) + 2)) / 16;
        motion->unk_10 = -(source->unk_10 * ((rand() & 1) + 2)) / 16;
        motion->unk_14 = (~rand() & 1) << 0xF;
        func_8003DB94(appearance, &D_800D1464, 0);
        appearance->color.c.b = 0xFF;
        appearance->color.c.g = 0xFF;
        appearance->color.c.r = 0xFF;
        appearance->scale_y = 0x1000;
        appearance->scale_x = 0x1000;
        appearance->tpage_abr = 0x60;
        appearance->flags |= 0xC;
        effect_params[1] = scale_random_to_unsigned_halfword_limit(7) + scale_random_to_unsigned_halfword_limit(7);
    }
    return effect;
}
