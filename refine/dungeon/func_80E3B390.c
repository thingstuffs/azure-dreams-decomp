#include "common.h"
#include "m2c_compat.h"

typedef struct S_80174B90_4 {
    u8 pad_00[0x14];
    void * unk_14;
} S_80174B90_4;   /* temp_s0 in func_80174B90 */

typedef struct S_80174B90_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174B90_5;   /* temp_v0 in func_80174B90 */

typedef struct S_80174B90_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174B90_6;   /* arg0 in func_80174B90 */

typedef struct S_80174B90_7 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80174B90_7;   /* ((S_80174B90_4 *)temp_s0)->unk_14 in func_80174B90 */

typedef struct S_80174B90_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174B90_8;   /* ((S_80174B90_5 *)temp_v0)->unk_08 in func_80174B90 */

typedef struct S_80174B90_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174B90_9;   /* ((S_80174B90_6 *)arg0)->unk_08 in func_80174B90 */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80047784();    /* extern */
extern M2C_UNK D_8017474C;
extern M2C_UNK D_80175540;

typedef struct S_80174B90_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80174B90_0;   /* temp_v0 in func_80174B90 */

typedef struct S_80174B90_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    void * unk_14;
    void * unk_18;
    s16 unk_1C;
} S_80174B90_1;   /* temp_s0 in func_80174B90 */

typedef struct S_80174B90_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80174B90_2;   /* arg0 in func_80174B90 */

typedef struct S_80174B90_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x8];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80174B90_3;   /* temp_a0 in func_80174B90 */

/* Create an effect using the source object's rendering and transform data. */
void func_80174B90(S_80174B90_2 *source, s32 state_00, s32 state_04, s32 state_08) {
    S_80174B90_3 *render_data;
    S_80174B90_1 *effect_state;
    void *effect;

    effect = func_8003FD64(0x100, source);
    if (effect != NULL) {
        render_data = ((S_80174B90_0 *)effect)->unk_0C;
        effect_state = effect + 0x20;
        ((S_80174B90_0 *)effect)->unk_10 = &D_8017474C;
        effect_state->unk_14 = (void *) source->unk_0C;
        effect_state->unk_18 = (void *) source->unk_08;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        render_data->unk_0C = 0x808080;
        render_data->unk_28 = (s32) ((S_80174B90_7 *)(((S_80174B90_4 *)effect_state)->unk_14))->unk_28;
        render_data->unk_12 = (u16) ((S_80174B90_7 *)(((S_80174B90_4 *)effect_state)->unk_14))->unk_12;
        ((S_80174B90_8 *)(((S_80174B90_5 *)effect)->unk_08))->unk_02 = (u16) ((S_80174B90_9 *)(((S_80174B90_6 *)source)->unk_08))->unk_02;
        ((S_80174B90_8 *)(((S_80174B90_5 *)effect)->unk_08))->unk_06 = (u16) ((S_80174B90_9 *)(((S_80174B90_6 *)source)->unk_08))->unk_06;
        ((S_80174B90_8 *)(((S_80174B90_5 *)effect)->unk_08))->unk_0A = (u16) ((S_80174B90_9 *)(((S_80174B90_6 *)source)->unk_08))->unk_0A;
        func_80047784(render_data, 0x46, 0);
        func_8004491C(effect, &D_80175540);
        ((S_80174B90_0 *)effect)->unk_20 = state_00;
        effect_state->unk_04 = state_04;
        effect_state->unk_08 = state_08;
        effect_state->unk_0C = source;
        effect_state->unk_1C = 0x1000;
    }
}
