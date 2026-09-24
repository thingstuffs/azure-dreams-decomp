#include "common.h"

typedef struct EffectState {
    u8 pad_00[0x2C];
    s16 size_x;
    s16 size_y;
    u8 pad_30[0x64];
    s32 seed;
    u8 pad_98[0x8];
    s32 scale;
} EffectState;

typedef struct Vec3u16 {
    u8 pad_00[0x2];
    u16 x;
    u8 pad_04[0x2];
    u16 y;
    u8 pad_08[0x2];
    u16 z;
} Vec3u16;

typedef struct RenderState {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 flags;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} RenderState;

typedef struct Effect {
    u8 pad_00[0x8];
    Vec3u16 *position;
    RenderState *render;
    void *handler;
    u8 pad_14[0xC];
    EffectState state;
} Effect;

extern void func_8003DB94(RenderState *, void *, s32);
extern Effect *func_8003FC64(s32);
extern void func_8004491C(Effect *, void *);
extern s32 rand(void);
extern u8 D_800244E4[];
extern u8 D_80045340[];
extern Vec3u16 D_80083780;
extern u8 D_800DE870[];

/* Creates an effect with randomized position offsets and initializes its rendering state. */
void func_8196B2F8(s32 unused_0, s32 unused_1, s32 unused_2, s16 x, s16 y, s16 z) {
    Effect *effect;
    EffectState *state;
    RenderState *render;
    Vec3u16 *position;
    s16 size;
    s32 jitter;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        state = &effect->state;
        size = (rand() & 7) + 0x20;
        state->size_x = size;
        state->size_y = size;
        effect->handler = D_800244E4;
        func_8004491C(effect, D_80045340);
        render = effect->render;
        render->flags |= 0xC;
        render->unk_10 = 0x60;
        render->flags |= 2;
        render->unk_06 = 0;
        position = effect->position;
        position->x = x;
        position->y = y;
        position->z = z;
        position->x += D_80083780.x;
        position->y += D_80083780.y;
        position->z += D_80083780.z;
        jitter = rand() & 0x1F;
        position->x -= 0x10;
        position->x += jitter;
        jitter = rand() & 0x1F;
        position->y -= 0x10;
        position->y += jitter;
        jitter = rand() & 0x1F;
        position->z -= 0x10;
        position->z += jitter;
        state->seed = rand();
        state->scale = 0x1000;
        render = effect->render;
        render->unk_1C = 0xC00;
        render->unk_1E = 0xC00;
        render->unk_0E = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        render->unk_12 = 0x7DCF;
        render->flags |= 0x100;
        func_8003DB94(render, D_800DE870, 0);
    }
}
