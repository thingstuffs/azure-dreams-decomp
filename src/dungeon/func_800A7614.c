#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004491C();
extern M2C_UNK func_80044A50();
extern M2C_UNK D_80083460;
extern M2C_UNK D_800C6AEC;

typedef struct S_800ACD74_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_800ACD74_0;   /* arg0 in func_800ACD74 */

typedef struct S_800ACD74_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    s8 unk_0F;
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
} S_800ACD74_1;   /* arg2 in func_800ACD74 */

typedef struct S_800ACD74_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800ACD74_2;   /* arg3 in func_800ACD74 */

void func_800ACD74(void *arg0, void *arg1, S_800ACD74_1 *arg2, S_800ACD74_2 *arg3) {
    void *temp_s0;
    u16 *state;

    ((S_800ACD74_0 *)arg0)->unk_9A = 0x13;
    ((S_800ACD74_0 *)arg0)->unk_9B = 0;
    ((S_800ACD74_0 *)arg0)->unk_8C = 0;
    arg2->unk_14 = (u16)(arg2->unk_14 & 0xF7FF);
    ((S_800ACD74_0 *)arg0)->unk_96 = 0;
    temp_s0 = arg0 - 0x20;
    state = (u16 *)&D_80083460;
    state[5] = (u16)(state[5] + 1);
    func_80044A50(temp_s0);
    func_8004491C(temp_s0, &D_800C6AEC);
    arg2->unk_0F = 0;
    arg2->unk_0E = 0;
    arg2->unk_0D = 0;
    arg2->unk_0C = 0;
    arg2->unk_10 = 0x20;
    arg2->unk_12 = (u16)(arg2->unk_12 - 0x80);
    arg3->unk_1C = (s32)(arg3->unk_1C | 0x10000000);
}
