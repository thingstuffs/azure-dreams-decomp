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

void func_80023158(S_80023158_0 *arg0, S_80023158_2 *arg1)
{
    s16 state;
    s32 count;
    u16 next_state;
    S_80023158_1 *obj;

    state = arg0->unk_18.s;
    obj = arg0->unk_00;

    switch (state) {
    case 0: {
        register s16 reset_count ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

        if (obj->unk_2C != 3) {
            break;
        }
        reset_count = 0x18;
        next_state = arg0->unk_18.u;
        arg0->unk_1A = reset_count;
        goto increment_state;
    }

    case 1:
        arg1->unk_04 += 0xFFF00000;
        if (!(rand(obj) & 7)) {
            func_800ABD74(arg1);
        }
        count = arg0->unk_1A - 1;
        arg0->unk_1A = count;
        if ((count << 16) > 0) {
            break;
        }
        next_state = arg0->unk_18.u;

increment_state:
        next_state++;
        arg0->unk_18.u = next_state;
        break;

    case 2:
        if (obj->unk_2C < 3) {
            arg0->unk_18.s = 0;
            arg1->unk_04 += 0x01400000;
        }
        break;
    }
}

/* MECHANISM: A natural switch restores retail's dispatch and 0/1/2 body order.
   Predecessor-specific state reloads feed the shared increment; s32 keeps the countdown unmasked.
   True-space naming and cross-call args produce the exact 0x20 s0/s1/ra frame.
   At 2.95.2-G0, case-local reset_count pinned to v1 after the compare closes coloring. */
