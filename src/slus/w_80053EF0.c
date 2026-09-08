#include "common.h"

/* Canonical status-block struct shared across the D_800847D0 family (see
   src/w_800559B4.c, src/w_8005440C.c, src/w_800544A4.c): flags1@0x0, flags2@0x4.
   Padded past 8 bytes (matches the canonical S_800847D0's real >0x30 size) so
   codegen uses %hi/%lo addressing rather than $gp-relative. */
typedef struct S_800847D0 {
    u32 flags1;   /* 0x00 */
    u32 flags2;   /* 0x04 */
    u32 pad8;     /* 0x08 */
} S_800847D0;

extern S_800847D0 D_800847D0;
extern s32 D_8008485C[3];
extern s32 D_800848FC[3];

/* Returns the blocking status for the selected mode from flags and pending state. */
s32 func_80053EF0(s32 mode) {
    s32 flags;

    switch (mode) {
    case 1:
        flags = D_800847D0.flags1;
        if (flags & 0x1000) {
            return 2;
        }
        if (D_800848FC[0] == 2) {
            return 3;
        }
        if (flags & 0x100) {
            return 1;
        }
        return 0;
    case 4:
        if (D_800847D0.flags2 & 0x200) {
            return 0x100;
        }
        flags = D_800847D0.flags1;
        if (flags & 0x4000) {
            return 2;
        }
        if (D_8008485C[0] == 2) {
            return 3;
        }
        if (flags & 0x400) {
            return 1;
        }
        return 0;
    default:
        return -1;
    }
}
