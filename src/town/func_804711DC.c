#include "common.h"

extern s32 D_8001B218[];

void func_80018198(void);
void func_8001844C(s32 arg0);
void func_8001A418(s32 arg0);

void func_800181DC(void) {
    u8 *entry;
    u8 *scan;
    u8 value;
    s32 message;

    entry = (u8 *)D_8001B218;
    value = entry[1];
    scan = entry + 1;
    if (value == 0) {
        return;
    }

loop:
    if ((value == 0x18) && (scan[2] & 0x20)) {
        value = entry[0];
        if (value == 0x20) {
            func_80018198();
            scan += 4;
            goto load_next;
        }
        if (value == 0x1C) {
            message = 0xD;
        } else {
            if (value != 0x1D) {
                goto common_messages;
            }
            message = 0xE;
        }
        func_8001A418(message);

common_messages:
        func_8001A418(entry[0] + 0x1497);
        func_8001A418(0x14C9);
        func_8001844C(entry[0]);
    }

    scan += 4;
load_next:
    value = scan[0];
    entry += 4;
    if (value != 0) {
        goto loop;
    }
}

/* MECHANISM: Two held byte pointers reproduce the retail s0/s1 loop state and
   its 0x20 early-call edge; the 0x1c/0x1d arms share one argumentized call.
   The true-space definition lets the in-row jumps remain ordinary CFG edges. */
