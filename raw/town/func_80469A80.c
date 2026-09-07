#include "common.h"

extern void func_8001A1A0(void *, void *);
extern void func_8001A200(void *, void *);
extern u8 D_8001791C[];
extern u8 D_80017AD0;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017E54[];

void *func_8001AA80(s32 arg0) {
    u8 *base = D_80017E54;

    *(s32 *)(base + 0xC) = *(s32 *)(D_8001791C + (arg0 * 0xC));
    func_8001A200(base, &D_80017AD0);
    func_8001A1A0(base + 0x14, &D_80017B0C);
    func_8001A1A0(base + 0x28, &D_80017B18);
    return base;
}

/* MECHANISM: Byte-addressed globals preserve the retail 12-byte table stride.
   One base pointer remains live across all calls, inducing the lone s0 save
   and the 24-byte nonleaf frame required by the callee ABI. */
