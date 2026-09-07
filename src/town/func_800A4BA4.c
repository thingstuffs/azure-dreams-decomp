#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_800A2000(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_800A2338;
extern M2C_UNK D_800A23D0;

M2C_UNK func_800A2304(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    return func_800A2000(arg0, arg1, arg2, arg3, &D_800A2338, &D_800A23D0);
}

/* MECHANISM: sp+0x10 and sp+0x14 are outgoing ABI slots for arguments 5 and 6,
   not volatile locals; forwarding incoming a0-a3 exposes the real six-argument call.
   The true-space rowbase name lets the second outgoing store occupy the jal delay slot. */
