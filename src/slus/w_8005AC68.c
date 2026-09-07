#include "common.h"

/* 0x1C-byte-stride slot table shared with func_80057A50 (D_80086A40). This
 * function clears a slot: if the slot's s16 marker (offset 0x00) is not -1,
 * it calls func_8005A1D0 with the slot's data pointer (offset 0x10), then
 * marks the slot free by setting the marker to -1. */
typedef struct {
    /* 0x00 */ s16 marker;
    /* 0x02 */ u8 pad02[2];
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u8 pad08[8];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[8];
} S_8005AC68; /* size 0x1C (28) */

extern S_8005AC68 D_80086A40[16];

extern void func_8005A1D0(s32 arg0);

void func_8005AC68(s16 arg0) {
    S_8005AC68 *base = D_80086A40;
    S_8005AC68 *p = &base[arg0];
    s16 cleared = -1;

    if (cleared != p->marker) {
        func_8005A1D0(p->unk10);
        p->marker = cleared;
    }
}
