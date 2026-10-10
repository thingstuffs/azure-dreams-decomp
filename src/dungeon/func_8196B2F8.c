#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"









extern u8 D_800DE870[];

/* Creates an effect with randomized position offsets and initializes its rendering state. */
void func_80024AF8(s32 unused_0, s32 unused_1, s32 unused_2, s16 x, s16 y, s16 z) {
    Effect *effect;
    EffectState *state;
    RenderState *render;
    Vec3u16 *position;
    s16 size;
    s32 jitter;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        state = &effect->payload.state;
        size = (rand() & 7) + 0x20;
        state->size_x = size;
        state->size_y = size;
        effect->callback.handler = func_800244E4;
        func_8004491C(effect, (s32)func_80045340);
        render = effect->visual.render;
        render->flags |= 0xC;
        render->unk_10 = 0x60;
        render->flags |= 2;
        render->unk_06 = 0;
        position = effect->coordinates.position;
        position->x = x;
        position->y = y;
        position->z = z;
        position->x += ((u16)D_80083780.x.w.i);
        position->y += ((u16)D_80083780.y.w.i);
        position->z += ((u16)D_80083780.z.w.i);
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
        render = effect->visual.render;
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
