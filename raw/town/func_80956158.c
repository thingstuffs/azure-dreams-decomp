#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 rand(void *);
extern void func_800ABD74(void *);

void func_80023158(void *arg0, void *arg1)
{
    s16 state;
    s32 count;
    u16 next_state;
    void *obj;

    state = FIELD(arg0, s16, 0x18);
    obj = FIELD(arg0, void *, 0);

    switch (state) {
    case 0: {
        register s16 reset_count ASM_REG("$3");

        if (FIELD(obj, s16, 0x2C) != 3) {
            break;
        }
        reset_count = 0x18;
        next_state = FIELD(arg0, u16, 0x18);
        ASM_KEEP(reset_count);
        FIELD(arg0, u16, 0x1A) = reset_count;
        goto increment_state;
    }

    case 1:
        FIELD(arg1, s32, 4) += 0xFFF00000;
        if (!(rand(obj) & 7)) {
            func_800ABD74(arg1);
        }
        count = FIELD(arg0, u16, 0x1A) - 1;
        FIELD(arg0, u16, 0x1A) = count;
        if ((count << 16) > 0) {
            break;
        }
        next_state = FIELD(arg0, u16, 0x18);

increment_state:
        next_state++;
        FIELD(arg0, u16, 0x18) = next_state;
        break;

    case 2:
        if (FIELD(obj, s16, 0x2C) < 3) {
            FIELD(arg0, s16, 0x18) = 0;
            FIELD(arg1, s32, 4) += 0x01400000;
        }
        break;
    }
}

/* MECHANISM: A natural switch restores retail's dispatch and 0/1/2 body order.
   Predecessor-specific state reloads feed the shared increment; s32 keeps the countdown unmasked.
   True-space naming and cross-call args produce the exact 0x20 s0/s1/ra frame.
   At 2.95.2-G0, case-local reset_count pinned to v1 after the compare closes coloring. */
