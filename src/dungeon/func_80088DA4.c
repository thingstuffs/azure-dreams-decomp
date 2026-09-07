#include "common.h"

typedef struct S_8008E504_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x80];
    void * unk_124;
} S_8008E504_0;   /* arg0 in func_8008E504 */

typedef struct S_8008E504_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8008E504_1;   /* arg1 in func_8008E504 */

typedef struct S_8008E504_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
    s16 unk_8A;
} S_8008E504_2;   /* arg3 in func_8008E504 */

typedef struct S_8008E504_3 {
    u8 pad_00[0x1C];
    volatile s32 unk_1C;
} S_8008E504_3;   /* temp_a0 in func_8008E504 */

typedef struct S_8008E504_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_8008E504_4;   /* arg2 in func_8008E504 */



extern volatile s32 D_80081484;
extern s32 D_800E3540;
extern u8 D_8008ACDC[];
extern u8 D_8008EAC8[];
extern u8 D_800DD058[];
extern s16 D_80083228[5];

extern void func_800419EC(s32, s32);
extern void func_80048A44(void *, u8, s32, s32);
extern s32 func_80094EA4(void);

void func_8008E504(S_8008E504_0 *arg0, S_8008E504_1 *arg1, S_8008E504_4 *arg2, S_8008E504_2 *arg3) {
    u16 temp_v0;
    u16 temp_v0_2;
    s32 temp_v1;
    s32 saved;
    s32 arg3_flags;
    s32 object_flags;
    S_8008E504_3 *temp_a0;

    temp_v1 = arg0->unk_9B;
    if (temp_v1 == 1) {
        goto state_one;
    }
    if (temp_v1 >= 2) {
        goto state_two_check;
    }
    if (temp_v1 == 0) {
        goto state_zero;
    }
    goto done;

state_two_check:
    temp_v0 = 2;
    if (temp_v1 == temp_v0) {
        goto state_two_body;
    }
    goto done;

state_zero:
    if (!(arg0->unk_A2 & 0x10)) {
        goto done;
    }
    arg1->unk_14 = 0;
    if ((arg3->unk_88 - arg3->unk_8A) < 0x41) {
        goto state_zero_short;
    }
    func_800419EC(8, 0x10);
    if (arg3->unk_1C & 0x100000) {
        temp_a0 = arg0->unk_124;
        saved = D_80081484;
        object_flags = temp_a0->unk_1C;
        D_80081484 = 0;
        temp_a0->unk_1C = object_flags & 0xFFF7FFFF;
        arg3_flags = arg3->unk_1C;
        D_800E3540 = saved;
        arg3->unk_1C = arg3_flags & 0xFFEFFFFF;
    }
    temp_v0 = 0xC;
    arg0->unk_96 = temp_v0;
    goto increment_state;

state_zero_short:
    arg0->unk_96 = 1U;

increment_state:
    arg0->unk_9B = (u8)(arg0->unk_9B + 1);

state_one:
    if (arg3->unk_1C & 0x100000) {
        arg0->unk_8C = D_8008EAC8;
        goto done;
    }
    arg2->unk_2C = D_800DD058;
    func_80048A44(arg2,
        D_800DD058[((D_80083228[0] + arg3->unk_2A + 0x100) >> 9) & 7],
        0, 1);
    arg2->unk_14 = (u16)(arg2->unk_14 | 0x800);
    arg0->unk_9B = (u8)(arg0->unk_9B + 1);
    goto done;

state_two_body:
    temp_v0 = arg0->unk_96 - 1;
    arg0->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto done;
    }
    temp_v0_2 = arg2->unk_14;
    arg2->unk_14 = (u16)(temp_v0_2 & 0xF7FF);
    if ((temp_v0_2 & 0xE000) != 0 || ((func_80094EA4() << 0x10) != 0)) {
        goto assign_dispatch;
    }
    goto done;

assign_dispatch:
    arg0->unk_8C = D_8008ACDC;

done:
    return;
}
