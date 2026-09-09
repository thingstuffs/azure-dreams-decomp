#include "common.h"
#include "m2c_compat.h"

typedef struct S_800F62BC_0_pre {
    u16 unk_00;
} S_800F62BC_0_pre;   /* the 0x2 bytes before state in func_800F62BC, addressed as state[-1] */

typedef struct S_800F62BC_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    s16 unk_02;
    s16 unk_04;
} S_800F62BC_0;   /* state in func_800F62BC */

typedef struct S_800F62BC_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_800F62BC_1;   /* actor in func_800F62BC */


s32 func_800644B8();                             /* extern */
extern s32 D_800814A0;
extern u8 D_80173AF8;

void func_800F62BC(void *arg0, s32 arg1, void *arg2) {
    s16 temp_v0_2;
    s32 temp_v0;
    register s32 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 temp_v1_2;
    void *state = arg0;
    void *actor = arg2;

    if (((S_800F62BC_0 *)state)->unk_00.s == 0) {
        temp_v0 = func_800644B8(((S_800F62BC_0 *)state)->unk_04 << 7) >> 6;
        temp_v1 = temp_v0 + 0x80;
        temp_v0 = (s32) (temp_v0 << 0x10) >> 0x11;
        temp_v1 += temp_v0;
        ((S_800F62BC_1 *)actor)->unk_0D = temp_v1;
        ((S_800F62BC_1 *)actor)->unk_0E = temp_v1;
        ((S_800F62BC_1 *)actor)->unk_0C = temp_v1;
        if (D_80173AF8 != 0) {
            ((S_800F62BC_0 *)state)->unk_02 = 0x20;
            ((S_800F62BC_0 *)state)->unk_00.u = (u16) (((S_800F62BC_0 *)state)->unk_00.u + 1);
        }
    } else {
        temp_v1_2 = ((S_800F62BC_1 *)actor)->unk_0C;
        temp_v1_2 -= (s32) temp_v1_2 / ((S_800F62BC_0 *)state)->unk_02;
        ((S_800F62BC_1 *)actor)->unk_0C = temp_v1_2;
        ((S_800F62BC_1 *)actor)->unk_0D = temp_v1_2;
        ((S_800F62BC_1 *)actor)->unk_0E = temp_v1_2;
        temp_v0_2 = (u16) ((S_800F62BC_0 *)state)->unk_02 - 1;
        ((S_800F62BC_0 *)state)->unk_02 = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800F62BC_0_pre *)state)[-1].unk_00 | 0x8000);
            D_800814A0 |= 0x8000;
        }
    }
    ((S_800F62BC_1 *)actor)->unk_1A = (u16) (((S_800F62BC_1 *)actor)->unk_1A + 0x40);
    ((S_800F62BC_0 *)state)->unk_04 = (s16) ((u16) ((S_800F62BC_0 *)state)->unk_04 + 1);
}
/* MECHANISM: Restored the dead middle arg so state/actor naturally hold in s0/s1 with frame 0x20.
   Rebuilt the shared-tail CFG and fade quotient; the noreturn helper exposes the retail tail j.
   A staged v1 color pin, kept before its stores, preserves +0x80 and hoists the global page load. */
