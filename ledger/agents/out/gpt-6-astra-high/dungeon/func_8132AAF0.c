#include "common.h"
#include "m2c_compat.h"

typedef struct S_801722F0_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801722F0_0;   /* D_80174CD8 in func_801722F0 */

typedef struct S_801722F0_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    s16 unk_18;
} S_801722F0_1;   /* temp_v1 in func_801722F0 */

typedef struct S_801722F0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801722F0_2;   /* temp_v0 in func_801722F0 */

typedef struct S_801722F0_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801722F0_3;   /* temp_a0 in func_801722F0 */

typedef struct S_801722F0_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801722F0_4;   /* temp_v1_2 in func_801722F0 */

typedef struct S_801722F0_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801722F0_5;   /* temp_s1 in func_801722F0 */


void *func_8003FC64();
M2C_UNK func_8004491C();
M2C_UNK func_8003DB94();
M2C_UNK func_800A56E0();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_80172274;
extern S_801722F0_0 *D_80174CD8;

/* Create an effect at the source position and play its sound. */
void func_801722F0(void) {
    S_801722F0_3 *sprite;
    void *setup_data;
    S_801722F0_5 *source_pos;
    void *effect;
    S_801722F0_1 *effect_params;
    S_801722F0_4 *effect_pos;

    source_pos = D_80174CD8->unk_08;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        setup_data = &D_80045340;
        effect_params = effect + 0x20;
        effect_params->unk_16 = 0x1E;
        effect_params->unk_18 = 0x1E;
        ((S_801722F0_2 *)effect)->unk_10 = &D_80172274;
        func_8004491C(effect, setup_data);
        sprite = ((S_801722F0_2 *)effect)->unk_0C;
        sprite->unk_06 = 0;
        effect_pos = ((S_801722F0_2 *)effect)->unk_08;
        effect_pos->unk_00 = (s32) source_pos->unk_00;
        effect_pos->unk_04 = (s32) source_pos->unk_04;
        effect_pos->unk_08 = (s32) source_pos->unk_08;
        sprite = ((S_801722F0_2 *)effect)->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0x80);
        func_8003DB94(sprite, &D_800DE870, 0);
        func_800A56E0(0x703);
    }
}
