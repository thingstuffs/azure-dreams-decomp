#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct Page8008 {
    u8 pad[0x14A0];
    u32 flags;
} Page8008;

void func_801743E8(void *arg0, void *arg1, void *arg2)
{
    s32 state;
    u16 value;
    register Page8008 *page ASM_REG("$3");

    state = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96)--;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto exit;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto exit;

state_0:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 3;
        goto exit;
    }
    FIELD(arg0, u16, 0x96) = 3;
    FIELD(arg0, u8, 0x9B)++;

state_1:
    value = FIELD(arg2, u16, 0x1E) - 0x50;
    FIELD(arg2, u16, 0x1E) = value;
    FIELD(arg2, u16, 0x1C) = value;
    if (FIELD(arg0, s16, 0x96) < 0) {
        state = 2;
        value = FIELD(arg0, u8, 0x9B);
        FIELD(arg0, u16, 0x96) = state;
        goto increment_state;
    }
    goto exit;

state_2:
    FIELD(arg1, s32, 8) += 0x28000;
    value = FIELD(arg2, u16, 0x1E) - 0x80;
    FIELD(arg2, u16, 0x1E) = value;
    FIELD(arg2, u16, 0x1C) = value;
    if (FIELD(arg0, s16, 0x96) >= 0) {
        goto exit;
    }
    value = FIELD(arg0, u8, 0x9B);

increment_state:
    value++;
    FIELD(arg0, u8, 0x9B) = value;
    goto exit;

state_3:
    page = (Page8008 *)0x80080000;
    ASM_KEEP(page);
    FIELD(arg0, u16, -2) |= 0x8000;
    page->flags |= 0x8000;

exit:
    return;
}

/* MECHANISM: True-space in-range jumps are local CFG, producing the frameless leaf.
   Separate counter/state live ranges give retail's v1/v0 shared-increment roles.
   A guarded v1 page pointer holds 0x80080000 for the 0x14A0 RMW displacement. */
