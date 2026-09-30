#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u8 color[3];
    u8 pad_03;
    union {
        s8 shade[3];
        s32 word;
    } out;
    s32 saved_out;
    u8 pad_0C[0x26];
    s16 scale;
    u8 pad_34[0x2];
    s16 x;
    u8 pad_38[0x8];
    s32 pos[3];
    s32 vel[3];
} Effect;

typedef struct {
    s32 xyz[3];
} Vec3;

/* Updates effect motion and color fading, flagging completion near its target or at zero brightness. */
void func_80AC5470(Effect *effect, Vec3 *position) {
    s16 next_scale;

    position->xyz[0] += effect->pos[0];
    position->xyz[1] += effect->pos[1];
    position->xyz[2] += effect->pos[2];
    effect->pos[0] += effect->vel[0];
    effect->pos[1] += effect->vel[1];
    effect->pos[2] += effect->vel[2];

    if (__builtin_abs(effect->x - *(s16 *)((u8 *)position + 2)) < 0x10) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }

    effect->out.shade[0] = effect->color[0] * effect->scale / 256;
    effect->out.shade[1] = effect->color[1] * effect->scale / 256;
    effect->out.shade[2] = effect->color[2] * effect->scale / 256;
    next_scale = (u16)effect->scale - 8;
    effect->scale = next_scale;
    effect->saved_out = effect->out.word;
    if (next_scale <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
