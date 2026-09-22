#include "common.h"
#include "m2c_compat.h"

typedef struct S_8080BCD4_0_pre {
    u16 unk_00;
} S_8080BCD4_0_pre;   /* the 0x2 bytes before arg0 in func_805268D4, addressed as arg0[-1] */

typedef struct S_8080BCD4_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    void * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_8080BCD4_0;   /* arg0 in func_805268D4 */

typedef struct S_8080BCD4_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8080BCD4_1;   /* temp_a1 in func_805268D4 */


extern s32 D_80084D5C;

void func_805268D4(void *arg0) {
    s16 temp_v1;
    u16 temp_v0;
    u16 next_state;
    u16 flags;
    S_8080BCD4_1 *temp_a1;

    temp_v1 = ((S_8080BCD4_0 *)arg0)->unk_00.s;
    temp_a1 = ((S_8080BCD4_0 *)arg0)->unk_04;
    if (temp_v1 == 0) {
        goto state_zero;
    }
    if (temp_v1 == 1) {
        goto state_one;
    }
    return;

state_zero:
    temp_v0 = ((S_8080BCD4_0 *)arg0)->unk_02 - 1;
    ((S_8080BCD4_0 *)arg0)->unk_02 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        next_state = ((S_8080BCD4_0 *)arg0)->unk_00.u;
        flags = ((S_8080BCD4_0 *)arg0)->unk_16;
        next_state++;
        flags &= 0xFFFD;
        ((S_8080BCD4_0 *)arg0)->unk_16 = flags;
        ((S_8080BCD4_0 *)arg0)->unk_00.u = next_state;
        return;
    }
    return;

state_one:
    if (temp_a1->unk_2A & 1) {
        ((S_8080BCD4_0_pre *)arg0)[-1].unk_00 = (u16) (((S_8080BCD4_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
    }
}

/* MECHANISM: A zero-argument noreturn declaration preserves the live $a0/$a1 ABI
   and lets maspsx elide the frame while converting both terminal calls to jumps.
   Explicit default/zero/one block order plus sibling u16 next-state and flag locals
   produce the retail CFG, interleaved loads, and tail-delay-slot counter store. */
