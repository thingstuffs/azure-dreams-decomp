#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800352FC(void);
extern void func_800A506C(void) __attribute__((noreturn));
extern u8 D_80082660;
extern s32 D_80082A38[];
extern u8 D_800A4F4C[];
extern u8 D_80100D98[];

void func_800A4F84(void *arg0) {
    u8 *state;
    u8 *table;
    void *value;
    s32 count;
    u8 index;

    if (func_800352FC() != 0) {
        state = (u8 *)D_80082A38;
        if (state[1] != 0) {
            FIELD(arg0, s32, 0x34) = 0;
        }

        value = FIELD(arg0, void *, 0x30);
        if (value != 0) {
            FIELD(arg0, void *, 0) = value;
            func_800A506C();
        }

        index = state[1];
        if ((u32)(index - 2) < 0x53U) {
            table = &D_80082660;
            value = FIELD(table + (state[1] * 8), void *, 4);
            if (value != 0) {
                FIELD(arg0, s32, 0) = FIELD(value, s32, 8);
                func_800A506C();
            }
            goto use_default;
        }

        if (index == 0) {
            count = FIELD(arg0, s32, 0x34) + 1;
            FIELD(arg0, s32, 0x34) = count;
            if (count < 9) {
                return;
            }
            FIELD(arg0, s32, 0x34) = 9;
        }

use_default:
        FIELD(arg0, void *, 0) = D_80100D98;
        func_800A506C();
    } else {
        FIELD(arg0, void *, 0) = D_80100D98;
        FIELD(arg0, void *, 0x24) = D_800A4F4C;
        FIELD(arg0, s32, 0x30) = 0;
    }
}

/* A 24-byte frame holds arg0 in the sole saved register s0 across calls.
 * Positive outer polarity emits initialization late; noreturn dispatcher sites
 * retain three store-filled tails. Natural state allocation gives retail's
 * split v0 page carrier and a0 low-half address without a hard-register pin.
 */
