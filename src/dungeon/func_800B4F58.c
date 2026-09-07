#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BA6B8_0_pre {
    u16 unk_00;
} S_800BA6B8_0_pre;   /* the 0x2 bytes before arg0 in func_800BA6B8, addressed as arg0[-1] */

typedef struct S_800BA6B8_0 {
    u8 pad_00[0x30];
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
} S_800BA6B8_0;   /* arg0 in func_800BA6B8 */

typedef struct S_800BA6B8_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800BA6B8_1;   /* arg2 in func_800BA6B8 */


s32 func_800644B8();                             /* extern */
extern M2C_UNK D_800814A0;
extern u16 D_80083164;
extern u16 D_800DF37C;

void func_800BA6B8(void *arg0, void *arg1, void *arg2) {
    s8 temp_a0;

    if (D_800DF37C != 0) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800BA6B8_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
    temp_a0 = (func_800644B8(D_80083164 << 8) >> 7) - 0x80;
    if (((S_800BA6B8_0 *)arg0)->unk_30 != 0) {
        ((S_800BA6B8_1 *)arg2)->unk_0C = temp_a0;
    }
    if (((S_800BA6B8_0 *)arg0)->unk_31 != 0) {
        ((S_800BA6B8_1 *)arg2)->unk_0D = temp_a0;
    }
    if (((S_800BA6B8_0 *)arg0)->unk_32 != 0) {
        ((S_800BA6B8_1 *)arg2)->unk_0E = temp_a0;
    }
}

/* MECHANISM: The three-slot ABI keeps arg0 in s0 and the live arg2 destination in s1.
   Direct scalar RMW on D_800814A0 emits one shared lui base with lw/sw at 0x14a0.
   Removing the erroneous base-plus-0x14A0 lvalue eliminated the one-word displacement cascade. */
