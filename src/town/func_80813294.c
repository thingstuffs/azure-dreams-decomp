#include "common.h"

typedef struct S_80813294_0 {
    void * unk_00;
    union { s16 s; u16 u; u16 p; } unk_04;   /* accessed as both */
    u16 unk_06;
} S_80813294_0;   /* arg0 in func_8052DE94 */

typedef struct S_80813294_1 {
    u8 pad_00[0x16];
    union { u16 s; volatile u16 u; } unk_16;   /* accessed as both */
} S_80813294_1;   /* arg2 in func_8052DE94 */

typedef struct S_80813294_2 {
    u8 pad_00[0x5C];
    s16 unk_5C;
} S_80813294_2;   /* ((S_80813294_0 *)arg0)->unk_00 in func_8052DE94 */

void func_8052DE94(S_80813294_0 *arg0, s32 unused, S_80813294_1 *arg2) {
    s32 state;

    state = arg0->unk_04.s;
    arg0->unk_06 = arg0->unk_06 - 1;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    if (((S_80813294_2 *)(arg0->unk_00))->unk_5C == 4) {
        arg0->unk_06 = 10;
        arg0->unk_04.p = arg0->unk_04.u + 1;
    }
    return;

state_1:
    arg2->unk_16.s = arg2->unk_16.s + 0x40;
    if ((s16)arg0->unk_06 > 0) {
        return;
    }
    arg0->unk_04.p = arg0->unk_04.u + 1;
    return;

state_2:
    arg2->unk_16.s = arg2->unk_16.s - 0x18;
    if (arg2->unk_16.u < 0x18U) {
        arg2->unk_16.s = 0;
        arg0->unk_04.s = 0;
    }
}
