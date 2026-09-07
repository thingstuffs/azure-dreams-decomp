#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    s32 word[6];
} Copy24;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

extern s32 func_8003DE58();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_80047784();
extern void func_80175CDC() __attribute__((noreturn));

extern s32 D_80045340;
extern u8 D_800DDC40[];
extern s32 D_80175978;

void *func_80E122F4(void *arg0, void *arg1, void *arg2)
{
    Vec3u16 offset;
    void *reference;
    register void *obj ASM_REG("$17");
    register void *arg2_reg ASM_REG("$16");
    register void *ret ASM_REG("$2");
    void *coords;
    void *child;
    void *part;
    s32 delta;

    arg2_reg = arg2;
    ASM_KEEP(arg2_reg);
    reference = FIELD(FIELD(arg0, void *, 0x60), void *, -0x18);
    obj = func_8003FC64(0x312);
    if (obj != 0) {
        FIELD(obj, s32 *, 0x10) = &D_80175978;
        func_8004491C(obj, &D_80045340);

        child = FIELD(obj, void *, 0xC);
        FIELD(child, s32, 0x28) = FIELD(arg2_reg, s32, 0x28);
        FIELD(child, s16, 0x1E) = 0x800;
        FIELD(child, s16, 0x1C) = 0x800;
        FIELD(child, s32, 0xC) = 0x808080;
        FIELD(child, u16, 0x14) |= 0xC;
        FIELD(child, u16, 0x10) |= 0x20;
        func_80047784(child, 0x47, 0);

        coords = FIELD(obj, void *, 8);
        FIELD(obj, Copy24, 0x24) = *(Copy24 *)arg1;

        offset.z = 0;
        offset.y = 0;
        offset.x = 0;
        part = (u8 *)obj + 0x20;
        if (func_8003DE58(FIELD(arg2_reg, void *, 8), arg2_reg, &offset, 1) != 0) {
            FIELD(part, u16, 6) += offset.x;
            FIELD(coords, u16, 2) = FIELD(part, u16, 6);
            FIELD(part, u16, 0xA) += offset.y;
            FIELD(coords, u16, 6) = FIELD(part, u16, 0xA);
            FIELD(part, u16, 0xE) += offset.z;
            FIELD(coords, u16, 0xA) = FIELD(part, u16, 0xE);
        }

        delta = FIELD(reference, s32, 0) - FIELD(part, s32, 4);
        if (delta < 0) {
            delta += 31;
        }
        delta >>= 5;
        FIELD(part, s32, 0x10) = delta;
        delta = FIELD(reference, s32, 4) - FIELD(part, s32, 8);
        if (delta < 0) {
            delta += 31;
        }
        delta >>= 5;
        FIELD(part, s32, 0x14) = delta;
        delta = (FIELD(reference, s32, 8) -
                 ((s32)D_800DDC40[FIELD(FIELD(arg0, void *, 0x60), u8, 0x13)] << 15) -
                 FIELD(part, s32, 0xC)) / 32;
        FIELD(part, s32, 0x18) = delta;
        ret = obj;
        ASM_TAILSLOT_PIN(ret);
        func_80175CDC();
        return obj;
    }
    return 0;
}

/* MECHANISM: Reverse-order Vec3 zero stores and explicit negative-add-31/shift CFGs reproduce retail scheduling.
   Guarded $s0/$s1/$v0 roles preserve the 0x38 frame and return carrier under the noreturn tail contract.
   ASM_TAILSLOT_PIN sinks move $v0,$s1 into the LEAD-18 tail j slot after the final store. */
