#include "common.h"

typedef struct S_80097AF8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_80097AF8_0;   /* arg0 in func_80097AF8 */

typedef struct S_80097AF8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80097AF8_1;   /* arg1 in func_80097AF8 */

typedef struct S_80097AF8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80097AF8_2;   /* arg2 in func_80097AF8 */

typedef struct S_80097AF8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_80097AF8_3;   /* global_base in func_80097AF8 */

typedef struct S_80097AF8_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    void * unk_5C;
} S_80097AF8_4;   /* arg3 in func_80097AF8 */



extern s32 D_80083460;
extern u8 D_80096384[];

extern void func_80099F04(void *);
extern void func_80099F70(void *);

/* Advance the timed motion sequence and select its continuation when status flags allow. */
void func_80097AF8(S_80097AF8_0 *actor, S_80097AF8_1 *motion, S_80097AF8_2 *status, S_80097AF8_4 *owner)
{
    s32 state;
    s32 owner_flags;
    u16 state_ticks;
    u8 next_state;
    u8 *shared_state;

    state = actor->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    state_ticks = actor->unk_96 - 1;
    actor->unk_96 = state_ticks;
    if ((state_ticks << 16) > 0) {
        goto done;
    }
    motion->unk_14 = 0xFFEA0000;
    next_state = actor->unk_9B;
    actor->unk_96 = 0;
    goto increment_state;

state_one:
    state_ticks = actor->unk_96 + 1;
    actor->unk_96 = state_ticks;
    if ((actor->unk_A2 & 0x10) == 0) {
        goto done;
    }
    if ((s16)state_ticks < 4) {
        goto done;
    }
    motion->unk_14 = 0;
    next_state = actor->unk_9B;

increment_state:
    next_state++;
    actor->unk_9B = next_state;
    goto done;

state_two:
    if ((status->unk_14 & 0x6000) == 0) {
        goto done;
    }
    shared_state = (u8 *)&D_80083460;
    if (((S_80097AF8_3 *)shared_state)->unk_0A != 0) {
        goto done;
    }
    owner_flags = owner->unk_1C;
    if (owner_flags & 0x200000) {
        owner->unk_1C = owner_flags & 0xFFDFFFFF;
        ((S_80097AF8_3 *)shared_state)->unk_02 |= 0x412;
        func_80099F70(owner->unk_5C);
        func_80099F04(owner->unk_5C);
    }
    actor->unk_8C = D_80096384;

done:
    return;
}
