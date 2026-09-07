#include "common.h"
#include "m2c_compat.h"

typedef struct S_807B0238_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_807B0238_3;   /* temp_v0 in func_807B0238 */

typedef struct S_807B0238_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_807B0238_4;   /* arg0 in func_807B0238 */

typedef struct S_807B0238_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807B0238_5;   /* ((S_807B0238_3 *)temp_v0)->unk_08 in func_807B0238 */

typedef struct S_807B0238_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_807B0238_6;   /* ((S_807B0238_4 *)arg0)->unk_08 in func_807B0238 */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800F7910;
extern M2C_UNK D_800FBE24;

typedef struct S_807B0238_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_807B0238_0;   /* temp_v0 in func_807B0238 */

typedef struct S_807B0238_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_807B0238_1;   /* temp_v1 in func_807B0238 */

typedef struct S_807B0238_2 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_807B0238_2;   /* temp_s0 in func_807B0238 */

/* Creates an effect at a randomized offset from the source and initializes its state. */
void func_807B0238(S_807B0238_4 *source, s16 state_value, s32 render_value) {
    S_807B0238_2 *effect_state;
    void *effect;
    S_807B0238_1 *render_data;

    effect = func_8003FD64(0x212, source);
    if (effect != NULL) {
        ((S_807B0238_0 *)effect)->unk_10 = &D_800F7910;
        func_8004491C(effect, &D_80045340);
        ((S_807B0238_5 *)(((S_807B0238_3 *)effect)->unk_08))->unk_02 = (s16) ((((S_807B0238_6 *)(source->unk_08))->unk_02 + (rand() & 0x3F)) - 0x20);
        ((S_807B0238_5 *)(((S_807B0238_3 *)effect)->unk_08))->unk_06 = (s16) ((((S_807B0238_6 *)(source->unk_08))->unk_06 + (rand() & 0x3F)) - 0x20);
        ((S_807B0238_5 *)(((S_807B0238_3 *)effect)->unk_08))->unk_0A = (s16) ((((S_807B0238_6 *)(source->unk_08))->unk_0A + (rand() & 0x3F)) - 0x20);
        render_data = ((S_807B0238_0 *)effect)->unk_0C;
        effect_state = effect + 0x20;
        render_data->unk_08 = &D_800FBE24;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        render_data->unk_0C = render_value;
        render_data->unk_06 = 8;
        effect_state->unk_14 = state_value;
        effect_state->unk_32 = (s16) ((rand() & 0xFF) | 0x80);
    }
}
