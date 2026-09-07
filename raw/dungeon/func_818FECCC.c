#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern s32 func_80069EF8(void);
extern void func_8004491C(void *, void *, void *);
extern u8 D_800241B0[];
extern u8 D_80024400[];

void func_818FECCC(
    void *arg0,
    s16 arg1,
    s32 arg2,
    s16 arg3,
    s32 arg4,
    s32 arg5,
    s32 arg6)
{
    register s32 held_arg4 ASM_REG("$18") = arg4;
    register void *held_arg0 ASM_REG("$17") = arg0;
    register s16 held_arg1 ASM_REG("$21") = arg1;
    register s32 held_arg2 ASM_REG("$23") = arg2;
    register s16 held_arg3 ASM_REG("$22") = arg3;
    register s32 held_arg5 ASM_REG("$19") = arg5;
    register s32 held_arg6 ASM_REG("$20") = arg6;
    register void *temp_s0 ASM_REG("$16");
    s32 random1;
    s32 random2;
    s32 random3;
    s32 offset1;
    s32 offset2;
    s32 offset3;
    s32 value1;
    s32 value2;
    s32 value3;
    u32 descriptor_page;
    register void *call_obj ASM_REG("$4");
    register void *call_data ASM_REG("$5");
    void *dest1;
    void *dest2;
    void *dest3;

    temp_s0 = func_8003FD64(0x211, held_arg0);
    if (temp_s0 != NULL) {
        descriptor_page = 0x80020000;
        ASM_KEEP(descriptor_page);
        FIELD(temp_s0, s32, 0x10) = descriptor_page + 0x4400;
        random1 = func_80069EF8() & 0x1F;
        value1 = FIELD(FIELD(held_arg0, void *, 8), u16, 2);
        dest1 = FIELD(temp_s0, void *, 8);
        value1 += random1;
        offset1 = held_arg4 - 0x10;
        value1 += offset1;
        FIELD(dest1, s16, 2) = (s16)value1;

        random2 = func_80069EF8() & 0x1F;
        value2 = FIELD(FIELD(held_arg0, void *, 8), u16, 6);
        dest2 = FIELD(temp_s0, void *, 8);
        value2 += random2;
        offset2 = held_arg5 - 0x10;
        value2 += offset2;
        FIELD(dest2, s16, 6) = (s16)value2;

        random3 = func_80069EF8();
        call_obj = temp_s0;
        call_data = &D_800241B0;
        ASM_USE2(call_obj, call_data);
        random3 &= 0x1F;
        ASM_KEEP(random3);
        value3 = FIELD(FIELD(held_arg0, void *, 8), u16, 0xA);
        temp_s0 = (u8 *)call_obj + 0x20;
        dest3 = FIELD(call_obj, void *, 8);
        value3 += random3;
        offset3 = held_arg6 + 0x10;
        value3 += offset3;
        FIELD(dest3, s16, 0xA) = (s16)value3;
        ASM_KEEP(held_arg4);
        ASM_KEEP(held_arg5);
        ASM_KEEP(held_arg0);
        ASM_KEEP(held_arg6);
        ASM_KEEP(temp_s0);
        FIELD(temp_s0, s16, 0x14) = held_arg1;
        ASM_KEEP(held_arg1);
        FIELD(temp_s0, s16, 0x32) = held_arg3;
        func_8004491C(call_obj, call_data, dest3);
        ASM_KEEP(held_arg3);
        FIELD(temp_s0, s32, 8) = held_arg2;
        ASM_KEEP(held_arg2);
    }
}
