#include "common.h"

extern s32 func_80016D98(s32);
extern s32 func_800178A8(void *, s32, s32);
extern s32 func_80017904(void *, s32, s32);
extern s32 func_80017960(void *, void *, s32, s32);
extern void func_80018594(s32);
extern s32 func_8001868C(s32);
extern s32 func_80018868(s32, s32);
extern void func_800188E8(s32, s32, s32);

extern u8 D_80018A0C;
extern u8 D_80018B94[16];
extern u8 D_8001B333[];
extern u8 D_8001B3D2[];

s32 func_80016B9C(s32 arg0, s32 unused, s32 arg2)
{
    register s32 held_arg0 ASM_REG("$19") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *base ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u32 page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 secondary_page;
    s32 result;
    s32 index;

    if (arg2 == 1) {
        return (s32) D_8001B3D2;
    }

    result = func_80016D98(arg2);
    if (result != 0) {
        return result;
    }

    secondary_page = 0x80020000;
    ASM_KEEP(secondary_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    page = 0x80020000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    base = (void *) (page - 0x75F4);
    result = func_80017960(base, (void *) (secondary_page - 0x746C),
                          held_arg0, arg2);
    ASM_KEEP(held_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    index = func_80018868(0x990, 2);

    if (arg2 != 0xB) {
        return result;
    }

    func_80018594(0x998);
    if (func_80017904(base, held_arg0, 0xB) == 0) {
        if (func_8001868C(0x997) == 0) {
            index++;
            if (index == 4) {
                index = 0;
            }
            func_800188E8(0x990, index, 2);
        }
    }

    if (func_800178A8(&D_80018A0C, held_arg0, arg2) == 0) {
        return result;
    }
    return (s32) D_8001B333;
}

/* MECHANISM: The true-space three-argument ABI and guarded s3/s4 roles restore
   the 0x28 frame; pinned a1/v0 page halves reproduce the two address sequences.
   Keeping arg0 after the first call preserves save order without fencing the
   final CFG backfills; == 0 supplies retail's word-59 beqz polarity. */
