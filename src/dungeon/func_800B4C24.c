#include "common.h"

extern void func_800BA414(void *arg0, s32 arg1, void *arg2, s16 arg3);
#ifdef NON_MATCHING
extern void func_800BA3D0(void *arg0, s32 arg1, void *arg2) __attribute__((noreturn));
#else
extern void func_800BA3D0(void) __attribute__((noreturn));
#endif

s32 func_800BA384(void *arg0, s32 arg1, u8 *arg2) {
    volatile s16 *scratch = (volatile s16 *)0x1F800000;
    register u8 *next ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 value ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 result;

    scratch[0x46] = 0;
    scratch[0x42] = 0;
    scratch[0x3E] = 0;
    scratch[0x3A] = 0;
    scratch[0x40] = -31;
    scratch[0x38] = -31;
    scratch[0x44] = 31;
    scratch[0x3C] = 31;
    scratch[0x3D] = -31;
    scratch[0x39] = -31;
    scratch[0x45] = 31;
    scratch[0x41] = 31;

    func_800BA414(arg0, arg1, arg2, *(s16 *)(arg2 + 6));
    next = *(u8 **)((u8 *)arg0 - 8);
    arg0 = next + 32;
    if (next != 0) {
        value = *(s32 *)(next + 8);
        next = *(u8 **)(next + 12);
        ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(next);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        func_800BA3D0(arg0, value, next);
#else
        func_800BA3D0();
#endif
    }
    ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    result = 0;
    return result;
}
