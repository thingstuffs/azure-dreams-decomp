#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0;

void func_80020360(void *arg0)
{
    s16 state;
    void *data;
    u16 value;
    u16 flags;
    u16 count;
    register u32 page ASM_REG("$3");

    state = FIELD(arg0, s16, 0);
    data = FIELD(arg0, void *, 4);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    value = FIELD(arg0, u16, 2) - 1;
    FIELD(arg0, u16, 2) = value;
    if ((value << 16) > 0) {
        return;
    }
    flags = FIELD(arg0, u16, 0x16);
    count = FIELD(arg0, u16, 0);
    flags &= 0xFFFD;
    count++;
    FIELD(arg0, u16, 0x16) = flags;
    FIELD(arg0, u16, 0) = count;
    return;

state_one:
    if (FIELD(data, u16, 0x2A) & 1) {
        page = 0x80080000;
        ASM_KEEP(page);
        FIELD(arg0, u16, -2) |= 0x8000;
        FIELD((void *)page, s32, 0x14A0) |= 0x8000;
    }
}

/* MECHANISM: Retail is a frameless leaf; both apparent jumps target the local epilogue.
   The state-zero arm uses sibling halfword temporaries so both loads precede both stores.
   A guarded $v1 page local holds 0x80080000 for the D_800814A0 RMW tail. */
