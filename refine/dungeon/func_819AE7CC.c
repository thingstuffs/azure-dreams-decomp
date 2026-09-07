#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s16 rand();                                /* extern */
extern M2C_UNK D_80025D28;
extern M2C_UNK D_80027460;
extern M2C_UNK D_800CEEFC;

typedef struct S_80025FCC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80025FCC_0;   /* temp_v0 in func_80025FCC */

typedef struct S_80025FCC_1 {
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
} S_80025FCC_1;   /* temp_v0_2 in func_80025FCC */

typedef struct S_80025FCC_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x1];
    s8 unk_0D;
    u8 pad_0E[0x2];
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80025FCC_2;   /* temp_v1 in func_80025FCC */

typedef struct S_80025FCC_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xE];
    s16 unk_30;
    u8 pad_32[0x4];
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x4];
    s16 unk_3E;
    s16 unk_40;
} S_80025FCC_3;   /* temp_s0 in func_80025FCC */

/* Creates an effect at the supplied position and initializes its rendering and state. */
void *func_80025FCC(s16 x, s16 y, s16 z, s16 effect_param) {
    S_80025FCC_3 *effect_state;
    void *effect;
    S_80025FCC_1 *position;
    S_80025FCC_2 *render_state;

    effect = func_8003FC64(0x202);
    if (effect != NULL) {
        ((S_80025FCC_0 *)effect)->unk_10 = &D_80025D28;
        func_8004491C(effect, &D_800CEEFC);
        position = ((S_80025FCC_0 *)effect)->unk_08;
        effect_state = effect + 0x20;
        position->unk_0E = x;
        position->unk_02 = x;
        position->unk_12 = y;
        position->unk_06 = y;
        position->unk_16 = z;
        position->unk_0A = z;
        render_state = ((S_80025FCC_0 *)effect)->unk_0C;
        render_state->unk_1E = 0x200;
        render_state->unk_1C = 0x200;
        render_state->unk_0D = 0x20;
        render_state->unk_14 = 0xC;
        render_state->unk_08 = &D_80027460;
        render_state->unk_10 = 0x20;
        effect_state->unk_30 = 0x20;
        effect_state->unk_3E = 0x10;
        effect_state->unk_36 = effect_param;
        effect_state->unk_40 = 0x18;
        effect_state->unk_38 = rand();
        effect_state->unk_1C = x;
        effect_state->unk_1E = y;
        effect_state->unk_20 = z;
    }
    return effect;
}
