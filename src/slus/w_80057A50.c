#include "common.h"

/* Address-of-tile helper: looks up the currently-selected floor/map "slot"
 * (index D_80086D50) in the 0x1C-byte-stride slot table D_80086A40, reads its
 * data-buffer pointer (field +0x04), and adds a row/col byte offset computed
 * from *arg0 (row) and arg1 (col) into a 32x?? grid with a fixed 0x820 header. */
typedef struct {
    /* 0x00 */ unsigned char pad00[4];   /* includes an s16 slot-marker (see sibling func_8005AC68) */
    /* 0x04 */ s32 unk04;                /* data-buffer base pointer, used here as a raw address */
    /* 0x08 */ unsigned char pad08[0x14];
} S_80057A50_D80086A40; /* size 0x1C (28) -- confirmed by index-scaling in this and sibling asm */

extern S_80057A50_D80086A40 D_80086A40[16];
extern s16 D_80086D50[8]; /* forced hi/lo access via size > 8 (see gp-vs-hilo-extern-size) */

s32 func_80057A50(s32 *arg0, s32 arg1) {
    s32 field = D_80086A40[D_80086D50[0]].unk04;
    s32 off = (((*arg0 << 4) + (arg1 & 0xFFFF)) << 5) + 0x820;
    return field + off;
}
