#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800B8CF0;
extern M2C_UNK D_800DF358;

typedef struct S_800B8D64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_800B8D64_0;   /* temp_v0 in func_800B8D64 */

typedef struct S_800B8D64_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800B8D64_1;   /* temp_v0_2 in func_800B8D64 */

typedef struct S_800B8D64_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800B8D64_2;   /* temp_v1 in func_800B8D64 */

/* Create and initialize an effect at the given position. */
void func_800B8D64(s16 x, s16 y, s16 z) {
    S_800B8D64_0 *effect;
    S_800B8D64_1 *position;
    S_800B8D64_2 *sprite;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect->unk_10 = &D_800B8CF0;
        func_8004491C(effect, &D_80045340);
        position = effect->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        sprite = effect->unk_0C;
        sprite->unk_08 = &D_800DF358;
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        effect->unk_22 = 6;
    }
}
