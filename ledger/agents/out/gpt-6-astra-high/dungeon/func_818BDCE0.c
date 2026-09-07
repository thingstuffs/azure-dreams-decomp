#include "common.h"

typedef struct S_818BDCE0_0_pre {
    u16 unk_00;
} S_818BDCE0_0_pre;   /* the 0x2 bytes before arg0 in func_818BDCE0, addressed as arg0[-1] */

typedef struct S_818BDCE0_0 {
    void * unk_00;
    u8 pad_04[0xC];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x2];
    s16 unk_14;
} S_818BDCE0_0;   /* arg0 in func_818BDCE0 */

typedef struct S_818BDCE0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BDCE0_1;   /* v1 in func_818BDCE0 */

typedef struct S_818BDCE0_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_818BDCE0_2;   /* arg2 in func_818BDCE0 */

typedef struct S_818BDCE0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDCE0_3;   /* arg1 in func_818BDCE0 */



extern s32 D_800814A0[];

/* Advance effect counters, motion, and rotation, and flag expiry when its timer exceeds the limit. */
void func_818BDCE0(void *effect, S_818BDCE0_3 *motion, S_818BDCE0_2 *rotation)
{
    S_818BDCE0_1 *counter_state;

    counter_state = ((S_818BDCE0_0 *)effect)->unk_00;
    counter_state->unk_14++;
    ((S_818BDCE0_0 *)effect)->unk_10.s++;
    rotation->unk_1A += 0x300;

    motion->unk_00 += motion->unk_0C;
    motion->unk_04 += motion->unk_10;
    motion->unk_08 += motion->unk_14;

    if (((S_818BDCE0_0 *)effect)->unk_10.u > ((S_818BDCE0_0 *)effect)->unk_14) {
        ((S_818BDCE0_0_pre *)effect)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
