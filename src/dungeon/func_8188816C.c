#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80025868;
extern M2C_UNK D_800263F8;
extern M2C_UNK D_80045340;

typedef struct S_8002596C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x26];
    s16 unk_3A;
} S_8002596C_0;   /* temp_v0 in func_8002596C */

typedef struct S_8002596C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_8002596C_1;   /* temp_s0 in func_8002596C */

typedef struct S_8002596C_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002596C_2;   /* temp_s0_2 in func_8002596C */

/* Create a sprite effect at the given position with a randomized rotation. */
void func_8002596C(s16 x, s16 y, s16 z) {
    S_8002596C_1 *transform;
    S_8002596C_2 *sprite;
    S_8002596C_0 *effect;

    effect = func_8003FC64(0x202);
    if (effect != NULL) {
        effect->unk_10 = &D_80025868;
        func_8004491C(effect, &D_80045340);
        transform = effect->unk_08;
        transform->unk_02 = x;
        transform->unk_06 = y;
        transform->unk_0A = z;
        transform->unk_0E = 0;
        transform->unk_12 = 0;
        transform->unk_16 = (s16) (rand() & 7);
        sprite = effect->unk_0C;
        sprite->unk_0C = 0x808080;
        func_8003DB94(sprite, &D_800263F8, 0);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_10 = 0x20;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        effect->unk_3A = 0x10;
    }
}
