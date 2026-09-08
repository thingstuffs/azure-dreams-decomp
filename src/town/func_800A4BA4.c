#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_800A2000(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_800A2338;
extern M2C_UNK D_800A23D0;

/* Forward four inputs to func_800A2000 with two fixed data pointers. */
M2C_UNK func_800A2304(M2C_UNK input_first, M2C_UNK input_second, M2C_UNK input_third, M2C_UNK input_fourth) {
    return func_800A2000(input_first, input_second, input_third, input_fourth, &D_800A2338, &D_800A23D0);
}

/* MECHANISM: sp+0x10 and sp+0x14 are outgoing ABI slots for arguments 5 and 6,
   not volatile locals; forwarding incoming a0-a3 exposes the real six-argument call.
   The true-space rowbase name lets the second outgoing store occupy the jal delay slot. */
