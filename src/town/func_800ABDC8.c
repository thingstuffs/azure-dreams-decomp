#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_800A9358(s32 arg2);

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
} Struct800ABDC8;

s32 func_800A9528(void *arg0, s32 arg1, s32 arg2) {
    register s32 v0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register Struct800ABDC8 *v1 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 x ASM_REG("$5");   /* UNRESOLVED C shape (pin): retail keeps this dead load in $a1; the source shape that makes it unnecessary has not been found */

    v0 = arg2;
    v1 = (Struct800ABDC8 *)arg0;
    for (;;) {
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_800A9358(v0);
        v0 = *(s32 *)((u8 *)v1 - 8);
        v1 = (Struct800ABDC8 *)((u8 *)v0 + 0x20);
        if (v0 == 0) {
            ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            return 0;
        }
           /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        x = ((Struct800ABDC8 *)v0)->unk08;
        ASM_KEEP(x);   /* UNRESOLVED C shape (pin): retail keeps this dead load; the source shape that makes it unnecessary has not been found */
        v0 = ((Struct800ABDC8 *)v0)->unk0C;
    }
}
