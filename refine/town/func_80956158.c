#include "common.h"

typedef struct S_80023158_0 {
    void * unk_00;
    u8 pad_04[0x14];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u16 unk_1A;
} S_80023158_0;   /* arg0 in func_80023158 */

typedef struct S_80023158_1 {
    u8 pad_00[0x2C];
    s16 unk_2C;
} S_80023158_1;   /* obj in func_80023158 */

typedef struct S_80023158_2 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80023158_2;   /* arg1 in func_80023158 */



extern s32 rand(void *);
extern void func_800ABD74(void *);

/* Runs a 24-tick value decrease with random callbacks, then waits to reset. */
void func_80023158(S_80023158_0 *sequence, S_80023158_2 *target)
{
    s16 state;
    s32 ticks_left;
    u16 next_state;
    S_80023158_1 *owner;

    state = sequence->unk_18.s;
    owner = sequence->unk_00;

    switch (state) {
    case 0: {
        register s16 duration ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

        if (owner->unk_2C != 3) {
            break;
        }
        duration = 0x18;
        next_state = sequence->unk_18.u;
        sequence->unk_1A = duration;
        goto increment_state;
    }

    case 1:
        target->unk_04 += 0xFFF00000;
        if (!(rand(owner) & 7)) {
            func_800ABD74(target);
        }
        ticks_left = sequence->unk_1A - 1;
        sequence->unk_1A = ticks_left;
        if ((ticks_left << 16) > 0) {
            break;
        }
        next_state = sequence->unk_18.u;

increment_state:
        next_state++;
        sequence->unk_18.u = next_state;
        break;

    case 2:
        if (owner->unk_2C < 3) {
            sequence->unk_18.s = 0;
            target->unk_04 += 0x01400000;
        }
        break;
    }
}
