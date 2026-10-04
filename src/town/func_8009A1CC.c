#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"


typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) \
(*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800374F4();
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_800ABB20;
extern s32 D_800D1464;

typedef struct S_8009792C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8009792C_0;   /* temp_v0 in func_8009792C */

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
} S_8009792C_1;   /* temp_s2 in func_8009792C */

typedef struct S_8009792C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_8009792C_2;   /* arg0 in func_8009792C */

typedef struct S_8009792C_3 {
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
} S_8009792C_3;   /* temp_s0 in func_8009792C */

/* Creates an offset effect with randomized motion and initializes its appearance. */
void *func_8009792C(S_8009792C_2 *source, u32 angle) {
    u32 direction;
    S_8009792C_3 *appearance;
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
        ((S_8009792C_0 *)effect)->unk_10 = (M2C_UNK *)&D_800ABB20;
        func_8004491C(effect, func_80045340);
        motion->unk_02 = source->unk_02 - dirStepX[direction] * 0x10;
        motion->unk_06 = source->unk_06 - dirStepY[direction] * 0x10;
        motion->unk_0A = source->unk_0A;
        motion->unk_0C = -(source->unk_0C * ((rand() & 1) + 2)) / 16;
        motion->unk_10 = -(source->unk_10 * ((rand() & 1) + 2)) / 16;
        motion->unk_14 = (~rand() & 1) << 0xF;
        func_8003DB94(appearance, &D_800D1464, 0);
        appearance->unk_0E = 0xFF;
        appearance->unk_0D = 0xFF;
        appearance->unk_0C = 0xFF;
        appearance->unk_1E = 0x1000;
        appearance->unk_1C = 0x1000;
        appearance->unk_10 = 0x60;
        appearance->unk_14 |= 0xC;
        effect_params[1] = func_800374F4(7) + func_800374F4(7);
    }
    return effect;
}
