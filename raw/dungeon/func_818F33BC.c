#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern s32 rand(void);
extern void func_8004491C(void *, void *);
extern void func_80024B6C(void);
extern void func_800248EC(void);

void func_80024BBC(
    void *arg0, s16 arg1, void *arg2, s16 arg3,
    s32 arg4, s32 arg5, s32 arg6)
{
    register s32 held_arg4 ASM_REG("$18") = arg4;
    register s32 held_arg5 ASM_REG("$19") = arg5;
    register s32 held_arg6 ASM_REG("$20") = arg6;
    void *object;
    void *base;

    object = func_8003FD64(0x211, arg0);
    if (object != NULL) {
        s32 random1;
        s32 random2;
        s32 random3;
        s32 offset1;
        s32 offset2;
        s32 offset3;
        s32 value1;
        s32 value2;
        s32 value3;
        void *dest1;
        void *dest2;
        void *dest3;

        FIELD(object, void *, 0x10) = func_80024B6C;

        random1 = rand() & 0x1F;
        value1 = FIELD(FIELD(arg0, void *, 8), u16, 2);
        dest1 = FIELD(object, void *, 8);
        value1 += random1;
        offset1 = held_arg4 - 0x10;
        value1 += offset1;
        FIELD(dest1, s16, 2) = value1;
        random2 = rand() & 0x1F;
        value2 = FIELD(FIELD(arg0, void *, 8), u16, 6);
        dest2 = FIELD(object, void *, 8);
        value2 += random2;
        offset2 = held_arg5 - 0x10;
        value2 += offset2;
        FIELD(dest2, s16, 6) = value2;

        base = (u8 *)object + 0x20;
        random3 = rand() & 0x1F;
        value3 = FIELD(FIELD(arg0, void *, 8), u16, 0xA);
        dest3 = FIELD(object, void *, 8);
        value3 += random3;
        offset3 = held_arg6 - 0x10;
        value3 += offset3;
        FIELD(dest3, s16, 0xA) = value3;
        FIELD(base, s16, 0x14) = arg1;
        FIELD(base, s16, 0x32) = arg3;
        func_8004491C(object, func_800248EC);
        FIELD(base, s32, 0x50) = -0x2000;
        FIELD(base, void *, 8) = arg2;
        ASM_KEEP(held_arg4);
        ASM_KEEP(held_arg5);
        ASM_KEEP(held_arg6);
    }
}

/* MECHANISM: The 0x38 frame and s2/s3/s4 stack-argument holds fall out of guarded pins.
   Separate random/value/destination/offset names give v1/a0/v0 one live range per field.
   Tail ASM_KEEPs prevent destructive saved-register updates without fencing call slots. */
