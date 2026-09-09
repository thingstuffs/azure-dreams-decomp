#include "common.h"
#include "m2c_compat.h"

typedef struct S_808127A4_0_pre {
    u16 unk_00;
} S_808127A4_0_pre;   /* the 0x2 bytes before arg0 in func_808127A4, addressed as arg0[-1] */

typedef struct S_808127A4_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; volatile u16 p; } unk_02;   /* accessed as both */
    s32 unk_04;
    u16 * unk_08;
    void * unk_0C;
    u8 pad_10[0x6];
    union { s16 s; u16 u; volatile u16 p; } unk_16;   /* accessed as both */
} S_808127A4_0;   /* arg0 in func_808127A4 */

typedef struct S_808127A4_1 {
    u8 pad_00[0x5C];
    s16 unk_5C;
} S_808127A4_1;   /* temp_s1 in func_808127A4 */


M2C_UNK func_80058588();           /* extern */
void func_8052D4A0(void) __attribute__((noreturn)); /* extern */
extern s32 D_80084D5C;

void func_808127A4(void *arg0) {
    s16 temp_v1;
    u32 temp_a0;
    u16 temp_step;
    u16 temp_v0;
    u16 temp_condition;
    void *temp_s1;

    temp_v1 = ((S_808127A4_0 *)arg0)->unk_00.s;
    temp_s1 = ((S_808127A4_0 *)arg0)->unk_0C;
    if (temp_v1 == 0) {
        goto state_0;
    }
    if (temp_v1 == 1) {
        goto state_1;
    }
    func_8052D4A0();
    return;

state_0:
    func_80058588(*((S_808127A4_0 *)arg0)->unk_08 * 0x3E8, 5, ((S_808127A4_0 *)arg0)->unk_04 + 4);
    if (((S_808127A4_1 *)temp_s1)->unk_5C != 3) {
        return;
    }
    if (((S_808127A4_0 *)arg0)->unk_16.s >= 0x78) {
        ((S_808127A4_0 *)arg0)->unk_02.s = 8;
    } else {
        ((S_808127A4_0 *)arg0)->unk_02.s = -8;
    }
    ((S_808127A4_0 *)arg0)->unk_00.u++;
    func_8052D4A0();
    return;

state_1:
    temp_a0 = ((S_808127A4_0 *)arg0)->unk_16.u;
    temp_step = ((S_808127A4_0 *)arg0)->unk_02.u;
    temp_v0 = ((S_808127A4_0 *)arg0)->unk_02.p;
    temp_a0 += temp_step;
    temp_v0 = temp_a0 + ((s32) (temp_v0 << 0x10) >> 0x12);
    temp_condition = (temp_v0 + 8) & 0xFFFF;
    ((S_808127A4_0 *)arg0)->unk_16.p = temp_a0;
    ((S_808127A4_0 *)arg0)->unk_16.u = temp_v0;
    if (temp_condition >= 0xF9U) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_808127A4_0_pre *)arg0)[-1].unk_00 | 0x8000);
        *(s32 *) 0x80084D5C = D_80084D5C | 0x8000;
    }
}

/* MECHANISM: Retail-order state labels preserve the 0x20 s0/s1 frame and CFG.
   Noreturn tails plus named fences hold both RMW and delay-slot store shapes.
   Split predicate/read lifetimes and signed s16 arm stores recover a0/v1/v0 roles.
   Symbolic load plus literal store forces independent global load/store bases. */
