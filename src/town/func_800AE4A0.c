#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800ABC00_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800ABC00_0;   /* temp_s1 in func_800ABC00 */

typedef struct S_800ABC00_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800ABC00_1;   /* held_arg0 in func_800ABC00 */

typedef struct S_800ABC00_2 {
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
} S_800ABC00_2;   /* temp_s0 in func_800ABC00 */

typedef struct S_800ABC00_3 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800ABC00_3;   /* temp_s2 in func_800ABC00 */



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

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 func_8003DB94();

extern s32 D_80045340;
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern s32 D_800ABB20;
extern s32 D_800D1464;

/* Spawns an offset effect with randomized motion opposite the source velocity. */
void func_800ABC00(void *source_data, u32 angle)
{
    S_800ABC00_1 *source;
    s16 *y_step;
    s16 *x_steps;
    u32 direction;
    S_800ABC00_2 *sprite;
    S_800ABC00_0 *motion;
    SubObject *effect_state;
    Object *effect;

    source = source_data;
    angle >>= 9;
    direction = angle & 7;
    effect = func_8003FC64(0x212, angle);
    if (effect != NULL) {
        motion = effect->unk8;
        sprite = effect->unkC;
        effect_state = &effect->sub20;
        effect->unk10 = &D_800ABB20;
        func_8004491C(effect, &D_80045340);
        x_steps = D_8006CCD8;
        y_step = &D_8006CCE8[direction];
        motion->unk_02 =
            (s16)(source->unk_02 -
                  (x_steps[direction] * 0x10));
        motion->unk_06 =
            (s16)(source->unk_06 - (*y_step * 0x10));
        motion->unk_0A = source->unk_0A;
        motion->unk_0C =
            0 - (source->unk_0C *
                 ((rand(y_step) & 1) + 2));
        motion->unk_10 =
            0 - (source->unk_10 *
                 ((rand() & 1) + 2));
        motion->unk_14 = (~rand() & 1) << 0xF;
        func_8003DB94(sprite, &D_800D1464, 0);
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_10 = 0x60;
        sprite->unk_14 |= 0xC;
        ((S_800ABC00_3 *)effect_state)->unk_02 = (rand() & 3) | 4;
    }
}
