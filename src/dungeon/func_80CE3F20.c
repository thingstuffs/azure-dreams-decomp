#include "common.h"

extern s32 func_800AC82C(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);

extern s16 D_80083228;
extern u8 D_8014CF20[];
extern u8 D_8014FB98[];
extern u8 D_801522C8[];
extern u8 D_80152300[];
extern u8 D_80152328[];
extern u8 D_80152360[];

void func_8014F720(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *obj0 = arg0;
    void *obj2 = arg2;
    register void *obj3 ASM_REG("$18") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *kind;
    register u8 *table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *entry;
    void *call_obj;
    s32 index;

    if (func_800AC82C(arg0, arg1, arg2, arg3) != 0) {
        if ((func_800AD9B4(obj2, obj3) << 0x10) > 0) {
            if (*(u8 *)((u8 *)obj0 + 0xA7) != 0) {
                *(void **)((u8 *)obj0 + 0x8C) = D_8014FB98;
            } else {
                *(void **)((u8 *)obj0 + 0x8C) = D_8014CF20;
            }
        }
        return;
    }

    kind = *(void **)((u8 *)obj2 + 0x2C);
    if (kind == D_80152300) {
        if (*(s32 *)((u8 *)obj3 + 0x1C) & 0x208) {
            return;
        }
        table = D_801522C8;
    } else if (kind == D_80152360) {
        if (*(s32 *)((u8 *)obj3 + 0x1C) & 0x208) {
            return;
        }
        table = D_80152328;
    } else {
        return;
    }

    *(void **)((u8 *)obj2 + 0x2C) = table;
    index = (D_80083228 + *(s16 *)((u8 *)obj3 + 0x2A) + 0x100) >> 9;
    call_obj = obj2;
    entry = (u8 *)((u32)(index & 7) + (u32)table);
    func_80047784(call_obj, *entry, 0);
}

/* MECHANISM: The 0x20 frame and s1/s0/s2 held arguments preserve the proven CFG.
   Pinned a0 call-object and v0 entry lifetimes fill the lh delay slot without length drift.
   Integer index-first address addition defeats pointer-first canonicalization at word 57. */
