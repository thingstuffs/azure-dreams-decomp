#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern s32 func_8009B4B0(void *, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, void *);
extern void *func_800A3D18();
extern void func_800CA444(void *, s32, void *, void *);
extern void func_800CA788(void *, s32, void *, void *);

s32 func_800CA93C(void *arg0, s32 arg1, void *arg2) {
    register void *obj0 = arg0;
    register s32 arg1_hold ASM_REG("$21") = arg1;
    register void *arg2_hold ASM_REG("$18") = arg2;
    register void *obj ASM_REG("$16");
    register s32 mask ASM_REG("$17");
    register void *other ASM_REG("$19");
    register void *call_arg0 ASM_REG("$4");
    s32 found;
    void *entry;

    call_arg0 = arg2_hold;
    obj = obj0;
    FIELD(obj, s32, 0x14) |= 0x2000;
    FIELD(obj, s32, 0x1C) |= 0x2000;
    FIELD(obj, void *, 0x60) = func_800A3D18(call_arg0, obj, 4);
    ASM_KEEP(call_arg0);
    ASM_KEEP(obj);

    mask = -0x2001;
    FIELD(obj, s32, 0x14) &= mask;
    entry = FIELD(obj, void *, 0x60);
    FIELD(obj, s32, 0x1C) &= mask;
    if (entry != 0) {
        other = FIELD(entry, void *, -0x14);
        FIELD(obj, s32, 0x14) |= 0x2000;
        FIELD(obj, s32, 0x1C) |= 0x2000;
        found = func_8009B4B0(
            obj,
            FIELD(arg2_hold, u8, 0x24),
            FIELD(arg2_hold, u8, 0x25));
        FIELD(obj, s32, 0x14) &= mask;
        FIELD(obj, s32, 0x1C) &= mask;
        if (found == (s32)FIELD(obj, void *, 0x60)) {
            ASM_KEEP(other);
            ASM_KEEP(mask);
            func_800CA788(obj, arg1_hold, arg2_hold, obj);
            return 0;
        }
        FIELD(obj, s16, 0x2A) = func_800A0818(
            FIELD(arg2_hold, u8, 0x24),
            FIELD(arg2_hold, u8, 0x25),
            FIELD(other, u8, 0x24),
            FIELD(other, u8, 0x25),
            (u8 *)obj + 0x98);
        FIELD(obj, u16, 0x46) |= 0x8000;
    }

    ASM_KEEP(obj0);
    ASM_KEEP(arg1_hold);
    ASM_KEEP(arg2_hold);
    ASM_KEEP(mask);
    func_800CA444(obj0, arg1_hold, arg2_hold, obj);
    return 0;
}

/* MECHANISM: the 0x38 frame holds natural s4 plus pinned s5/s2/s0/s1/s3 roles.
   Selective DEPIN of obj0 preserves natural s4 but makes the first call source s0;
   the post-call s0 keep splits later live ranges without disturbing call setup. */
