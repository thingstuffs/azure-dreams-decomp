#include "common.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

typedef struct S_80164ED0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80164ED0_2;   /* temp_v0 in func_80164ED0 */

typedef struct S_80164ED0_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80164ED0_3;   /* arg0 in func_80164ED0 */

typedef struct S_80164ED0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80164ED0_4;   /* ((S_80164ED0_2 *)temp_v0)->unk_08 in func_80164ED0 */

typedef struct S_80164ED0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80164ED0_5;   /* ((S_80164ED0_3 *)arg0)->unk_08 in func_80164ED0 */

typedef struct S_80164ED0_6 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80164ED0_6;   /* ((S_80164ED0_2 *)temp_v0)->unk_0C in func_80164ED0 */


void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern u8 D_80164BC4[];
extern u8 D_80164DA4[];

typedef struct S_80164ED0_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80164ED0_0;   /* temp_v0 in func_80164ED0 */

typedef struct S_80164ED0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_80164ED0_1;   /* temp_s0 in func_80164ED0 */

/* Creates an effect relative to its parent with randomized motion and initial state values. */
void func_80164ED0(S_80164ED0_3 *parent, s32 state_value, s16 pair_value, s32 offset_x, s32 offset_y, s32 offset_z)
{
    register s32 saved_offset_y ASM_REG("$19") = offset_y;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 saved_offset_z ASM_REG("$20") = offset_z;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    S_80164ED0_1 *effect_data;
    void *effect;

    effect = func_8003FD64(0x211, parent);
    if (effect != NULL) {
        ((S_80164ED0_0 *)effect)->unk_10 = D_80164DA4;
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)effect)->unk_08))->unk_02 = (s16)
            (((S_80164ED0_5 *)(parent->unk_08))->unk_02 + offset_x);
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)effect)->unk_08))->unk_06 = (s16)
            (((S_80164ED0_5 *)(parent->unk_08))->unk_06 + saved_offset_y);
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)effect)->unk_08))->unk_0A = (s16)
            (((S_80164ED0_5 *)(parent->unk_08))->unk_0A + saved_offset_z);
        ((S_80164ED0_6 *)(((S_80164ED0_2 *)effect)->unk_0C))->unk_06 = 6;
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)effect)->unk_08))->unk_0C = (s32)
            (((rand() & 0x7FFF) - 0x4000) << 6);
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)effect)->unk_08))->unk_10 = (s32)
            (((rand() & 0x7FFF) - 0x4000) << 6);
        effect_data = effect + 0x20;
        ((S_80164ED0_4 *)(((S_80164ED0_2 *)effect)->unk_08))->unk_14 = (s32)
            (((rand() & 0x7FFF) - 0x4000) << 6);
        effect_data->unk_32 = pair_value;
        effect_data->unk_34 = pair_value;
        func_8004491C(effect, D_80164BC4);
        ((S_80164ED0_0 *)effect)->unk_20 = state_value;
        effect_data->unk_08 = state_value;
    }
}
