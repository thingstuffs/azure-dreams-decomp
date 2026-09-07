#include "common.h"

extern s32 func_800AC82C(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);

extern s16 D_80083228;
extern u8 D_8015EF20[];
extern u8 D_80161B98[];
extern u8 D_801642C8[];
extern u8 D_80164300[];
extern u8 D_80164328[];
extern u8 D_80164360[];

void func_80161720(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *obj0 ASM_REG("$17") = arg0;
    register void *obj2 ASM_REG("$16") = arg2;
    register void *obj3 ASM_REG("$18") = arg3;
    void *kind;
    register u8 *table ASM_REG("$5");
    register u8 *entry ASM_REG("$2");
    register void *call_obj ASM_REG("$4");
    s32 index;

    if (func_800AC82C(arg0, arg1, arg2, arg3) != 0) {
        if ((func_800AD9B4(obj2, obj3) << 0x10) > 0) {
            if (*(u8 *)((u8 *)obj0 + 0xA7) != 0) {
                *(void **)((u8 *)obj0 + 0x8C) = D_80161B98;
            } else {
                *(void **)((u8 *)obj0 + 0x8C) = D_8015EF20;
            }
        }
        return;
    }

    kind = *(void **)((u8 *)obj2 + 0x2C);
    if (kind == D_80164300) {
        if (*(s32 *)((u8 *)obj3 + 0x1C) & 0x208) {
            return;
        }
        table = D_801642C8;
    } else if (kind == D_80164360) {
        if (*(s32 *)((u8 *)obj3 + 0x1C) & 0x208) {
            return;
        }
        table = D_80164328;
    } else {
        return;
    }

    *(void **)((u8 *)obj2 + 0x2C) = table;
    index = (D_80083228 + *(s16 *)((u8 *)obj3 + 0x2A) + 0x100) >> 9;
    call_obj = obj2;
    ASM_KEEP(call_obj);
    entry = (u8 *)((u32)(index & 7) + (u32)table);
    ASM_KEEP(entry);
    func_80047784(call_obj, *entry, 0);
}

/* MECHANISM: The 0x20 frame and s1/s0/s2 held arguments preserve the proven CFG.
   Pinned a0 call-object and v0 entry lifetimes fill the lh delay slot without length drift.
   Integer index-first address addition defeats pointer-first canonicalization at word 57. */
