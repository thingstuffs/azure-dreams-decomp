#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A2B04();              /* extern */
s16 func_800BCB04();                   /* extern */
extern s32 D_80083460[3];

typedef struct S_800AC480_0 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
} S_800AC480_0;   /* arg0 in func_800AC480 */

typedef struct S_800AC480_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800AC480_1;   /* arg2 in func_800AC480 */

typedef struct S_800AC480_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800AC480_2;   /* arg1 in func_800AC480 */

typedef struct S_800AC480_3 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_800AC480_3;   /* arg3 in func_800AC480 */

typedef struct S_800AC480_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AC480_4;   /* global_base in func_800AC480 */

s32 func_800AC480(S_800AC480_0 *arg0, S_800AC480_2 *arg1, S_800AC480_1 *arg2, S_800AC480_3 *arg3) {
    s32 calc;
    s32 field;
    s32 *global_base;
    s32 step;
    s16 temp_a1;
    s16 temp_v0;
    s16 temp_v0_2;

    temp_a1 = arg0->unk_96;
    if (temp_a1 != 0) {
        calc = arg2->unk_24 << 6;
        field = arg1->unk_02;
        field -= 0x20;
        calc -= field;
        step = (calc << 0x10) / temp_a1;
        field = arg1->unk_06;
        arg1->unk_0C = step;
        calc = arg2->unk_25 << 6;
        field -= 0x20;
        calc -= field;
        arg1->unk_10 = (calc << 0x10) / (s16) arg0->unk_96;
    }
    temp_v0 = (u16) arg0->unk_96 - 1;
    arg0->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        temp_v0_2 = func_800BCB04((arg2->unk_24 << 6) | 0x20, (arg2->unk_25 << 6) | 0x20, (s16) (arg3->unk_88 - 0x20));
        if (temp_v0_2 < 0x200) {
            arg0->unk_92 = (u16) (arg0->unk_92 + (arg3->unk_88 - temp_v0_2));
            arg3->unk_88 = (u16) temp_v0_2;
        }
        global_base = D_80083460;
        ASM_KEEP(global_base);   /* MATCH pin: load-bearing for the whole function shape */
        ((S_800AC480_4 *)global_base)->unk_0A = (u16) (((S_800AC480_4 *)global_base)->unk_0A - 1);
        return 1;
    }
    return 0;
}

/* MECHANISM: Explicit s32 calc/field/step lifetimes preserve each field-0x20
   subtraction and hoist the second lh into the first division's load-delay gap.
   Direct 0/1 returns plus a kept absolute D_80083460 base produce the retail
   v0 delay-slot value and a0-based lhu/sh tail without changing the 0x20 frame. */
