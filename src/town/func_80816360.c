#include "common.h"

typedef struct S_80020360_0_pre {
    u16 unk_00;
} S_80020360_0_pre;   /* the 0x2 bytes before arg0 in func_80020360, addressed as arg0[-1] */

typedef struct S_80020360_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    void * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_80020360_0;   /* arg0 in func_80020360 */

typedef struct S_80020360_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80020360_1;   /* data in func_80020360 */

typedef struct S_80020360_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80020360_2;   /* (void *)page in func_80020360 */



extern s32 D_800814A0;

/* Advances the countdown state, then sets object and global flags when the status bit is set. */
void func_80020360(void *object)
{
    s16 state;
    S_80020360_1 *status_data;
    u16 ticks_left;
    u16 flags;
    u16 next_state;
    u32 page;

    state = ((S_80020360_0 *)object)->unk_00.s;
    status_data = ((S_80020360_0 *)object)->unk_04;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    ticks_left = ((S_80020360_0 *)object)->unk_02 - 1;
    ((S_80020360_0 *)object)->unk_02 = ticks_left;
    if ((ticks_left << 16) > 0) {
        return;
    }
    flags = ((S_80020360_0 *)object)->unk_16;
    next_state = ((S_80020360_0 *)object)->unk_00.u;
    flags &= 0xFFFD;
    next_state++;
    ((S_80020360_0 *)object)->unk_16 = flags;
    ((S_80020360_0 *)object)->unk_00.u = next_state;
    return;

state_one:
    if (status_data->unk_2A & 1) {
        page = 0x80080000;
        ASM_KEEP(page);
        ((S_80020360_0_pre *)object)[-1].unk_00 |= 0x8000;
        do {
            ((S_80020360_2 *)((void *)page))->unk_14A0 |= 0x8000;
        } while (0);
    }
}
