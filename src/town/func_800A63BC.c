#include "common.h"

extern s32 func_800A3B80(void *, s32, void *);

/* Process linked states until a nonzero signed 16-bit result or the end of the chain. */
s32 func_800A3B1C(void *initial_state) {
    u8 *state = initial_state;
    u8 *carrier2;
    s32 carrier1;
    u16 result;

    for (;;) {
        result = func_800A3B80(state, carrier1, carrier2);
        if ((result << 0x10) != 0) {
            return (s16)result;
        }

        carrier2 = *(u8 **)(state - 8);
        if (carrier2 == 0) {
            return (s16)result;
        }

        state = carrier2 + 0x20;
        carrier1 = *(s32 *)(carrier2 + 8);
        carrier2 = (u8 *)(u32)*(s32 *)(carrier2 + 0xC);
    }
}
