#include "common.h"

extern void func_80017B3C(void *, s32);
extern s32 func_80017F8C(void *, s32, s32);
typedef struct {
    u8 pad0[8];
    s32 count;
    u8 pad1[52];
    u8 *table;
} Context;
extern Context *D_80016000;
extern s32 D_80018AF8;
extern s32 D_80019A30;

s32 *func_804B7B30(s32 arg0, s32 unused, s32 arg2) {
    Context *base;
    u8 *entry;
    s32 *countp;
    u8 **tablep;
    u32 offset;

    func_80017B3C(&D_80018AF8, arg0);
    if (arg2 == 10 && func_80017F8C(&D_80018AF8, arg0, 10) == 0) {
        base = D_80016000;
        countp = (s32 *)((u8 *)base + 8);
        tablep = (u8 **)((u8 *)base + 0x40);
        offset = *countp * 8;
        entry = (u8 *)(offset + (u32)*tablep);
        
        *entry += 1;
    }
    return &D_80019A30;
}

/* MECHANISM: A real dead middle parameter places the long-lived selector in a2/s0.
   The shared constant return removes the two-word false 0x80020000 initialization;
   one local base reproduces the single D_80016000 pointer load and byte update. */
