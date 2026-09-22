#include "common.h"

extern s32 func_80016250(u32);
extern void func_800193E0(s32);

extern s32 D_8001967C[];
extern s32 D_80019770[];
extern u8 D_8001AAEC[];
extern u8 D_8001DE58[];

/* Return the table for the selector: 8 plays a cue and resolves by state, 1 picks one of two blobs. */
s32 func_805D3208(s32 unused_a, s32 unused_b, s32 selector) {
    s32 result = 0;

    if (selector == 8) {
        func_800193E0(0x147A);
        result = func_80016250(D_80019770[D_8001967C[0]]);
    } else if (selector == 1) {
        if (D_8001967C[0] != 3) {
            result = (s32)D_8001DE58;
        } else {
            result = (s32)D_8001AAEC;
        }
    }

    return result;
}

/* MECHANISM: The 0x18 ra-only frame and the single-exit `result` shape are retail's:
   the row's two `j 0x80017284` words are jumps to its own epilogue (true base
   0x80017208, target row+0x7C = `lw ra`), each with the arm's value for the common
   `move v0,v1` in the delay slot. */
