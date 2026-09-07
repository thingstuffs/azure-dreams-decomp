#include "common.h"

typedef struct S_800A4F84_0 {
    union { void * s; s32 u; } unk_00;   /* accessed as both */
    u8 pad_04[0x20];
    void * unk_24;
    u8 pad_28[0x8];
    union { void * s; s32 u; } unk_30;   /* accessed as both */
    s32 unk_34;
} S_800A4F84_0;   /* arg0 in func_800A4F84 */

typedef struct S_800A4F84_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800A4F84_1;   /* table + (state[1] * 8) in func_800A4F84 */

typedef struct S_800A4F84_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A4F84_2;   /* value in func_800A4F84 */



extern s32 func_800352FC(void);
extern u8 D_80082660;
extern s32 D_80082A38[];
extern u8 D_800A4F4C[];
extern u8 D_80100D98[];

void func_800A4F84(S_800A4F84_0 *arg0) {
    u8 *state;
    u8 *table;
    S_800A4F84_2 *value;
    s32 count;
    u8 index;

    if (func_800352FC() != 0) {
        state = (u8 *)D_80082A38;
        if (state[1] != 0) {
            arg0->unk_34 = 0;
        }

        value = arg0->unk_30.s;
        if (value != 0) {
            arg0->unk_00.s = value;
            return;
        }

        index = state[1];
        if ((u32)(index - 2) < 0x53U) {
            table = &D_80082660;
            value = ((S_800A4F84_1 *)(table + (state[1] * 8)))->unk_04;
            if (value != 0) {
                arg0->unk_00.u = value->unk_08;
                return;
            }
            goto use_default;
        }

        if (index == 0) {
            count = arg0->unk_34 + 1;
            arg0->unk_34 = count;
            if (count < 9) {
                return;
            }
            arg0->unk_34 = 9;
        }

use_default:
        arg0->unk_00.s = D_80100D98;
        return;
    } else {
        arg0->unk_00.s = D_80100D98;
        arg0->unk_24 = D_800A4F4C;
        arg0->unk_30.u = 0;
    }
}

/* A 24-byte frame holds arg0 in the sole saved register s0 across calls.
 * Positive outer polarity emits initialization late; noreturn dispatcher sites
 * retain three store-filled tails. Natural state allocation gives retail's
 * split v0 page carrier and a0 low-half address without a hard-register pin.
 */
