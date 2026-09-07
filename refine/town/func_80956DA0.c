#include "common.h"
#include "m2c_compat.h"

typedef struct S_80956DA0_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80956DA0_3;   /* temp_v0 in func_80956DA0 */

typedef struct S_80956DA0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80956DA0_4;   /* ((S_80956DA0_3 *)temp_v0)->unk_08 in func_80956DA0 */




void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80023E64;
extern M2C_UNK D_80044BB0;
extern M2C_UNK D_80079438;

typedef struct S_80956DA0_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80956DA0_0;   /* temp_v0 in func_80956DA0 */

typedef struct S_80956DA0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80956DA0_1;   /* temp_v2 in func_80956DA0 */

typedef struct S_80956DA0_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80956DA0_2;   /* temp_v1 in func_80956DA0 */

/* Creates an object with user data and initializes its position and rendering state. */
void func_80956DA0(s32 user_data) {
    void *object;
    S_80956DA0_2 *render_state;
    S_80956DA0_1 *instance_data;
    s32 color;

    object = func_8003FC64(0x15);
    if (object != NULL) {
        ((S_80956DA0_0 *)object)->unk_10 = &D_80023E64;
        func_8004491C(object, &D_80044BB0);
        color = 0x800000;
        ASM_KEEP(color);   /* MATCH pin: retail schedule: same instructions, different order without it */
        render_state = ((S_80956DA0_0 *)object)->unk_0C;
        ASM_KEEP(render_state);   /* MATCH pin: retail schedule: same instructions, different order without it */
        instance_data = (u8 *)object + 0x20;
        ASM_KEEP(instance_data);   /* MATCH pin: retail basic-block layout depends on it */
        instance_data->unk_04 = user_data;
        ((S_80956DA0_4 *)(((S_80956DA0_3 *)object)->unk_08))->unk_02 = 0xF0;
        ((S_80956DA0_4 *)(((S_80956DA0_3 *)object)->unk_08))->unk_06 = 0xAC;
        ((S_80956DA0_4 *)(((S_80956DA0_3 *)object)->unk_08))->unk_0A = 0;
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_06 = 0x10;
        render_state->unk_08 = &D_80079438;
        render_state->unk_04 = 0;
        render_state->unk_05 = 0;
        color |= 0x8080;
        render_state->unk_0C = color;
        render_state->unk_14 = (u16) (render_state->unk_14 | 0xC);
    }
}
