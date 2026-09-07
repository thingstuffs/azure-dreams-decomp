#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800AA888_3 {
    u8 pad_00[0x60];
    void * unk_60;
} S_800AA888_3;   /* arg3 in func_800AA888 */

typedef struct S_800AA888_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800AA888_4;   /* ((S_800AA888_3 *)arg3)->unk_60 in func_800AA888 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8009A3D0();

typedef struct S_800AA888_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_800AA888_0;   /* arg0 in func_800AA888 */

typedef struct S_800AA888_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800AA888_1;   /* arg2 in func_800AA888 */

typedef struct S_800AA888_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_800AA888_2;   /* arg3 in func_800AA888 */

void func_800AA888(S_800AA888_0 *arg0, void *arg1, S_800AA888_1 *arg2, S_800AA888_2 *arg3) {
    u8 call_arg0;
    u8 call_arg1;
    M2C_UNK var_v1;

    arg0->unk_9A = 0xB;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    call_arg0 = arg2->unk_24;
    call_arg1 = arg2->unk_25;
    var_v1 = 0x3000;
    if (arg3->unk_1C & 0x2000) {
        var_v1 = 0x300;
    }
    func_8009A3D0(call_arg0, call_arg1, var_v1);
    arg0->unk_98 = (u16)(arg0->unk_98 | 8);
    arg3->unk_1C = (s32)(arg3->unk_1C & 0xFFFBFFFF);
    arg0->unk_96 = 0;
    arg3->unk_6A = (u16)((S_800AA888_4 *)(((S_800AA888_3 *)arg3)->unk_60))->unk_2A;
}

/* MECHANISM: Named u8 call-argument locals force both byte loads before the flag branch,
   freeing v1 to carry the selected third argument into the jal delay slot.
   Natural arg0/arg3 lifetimes yield the exact 0x20 frame and s0/s1 save order. */
