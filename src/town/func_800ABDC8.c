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

/* Process the initial value and each linked record value until the chain ends. */
s32 func_800A9528(void *object, s32 unused, s32 initial_value) {
    register s32 x ASM_REG("$5");   /* UNRESOLVED C shape (pin): retail keeps this dead load in $a1; the source shape that makes it unnecessary has not been found */

    unused = initial_value;
    object = (Struct800ABDC8 *)object;
    for (;;) {
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_800A9358(unused);
        unused = *(s32 *)((u8 *)object - 8);
        object = (Struct800ABDC8 *)((u8 *)unused + 0x20);
        if (unused == 0) {
            break;
        }
           /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        x = ((Struct800ABDC8 *)unused)->unk08;
        ASM_KEEP(x);   /* UNRESOLVED C shape (pin): retail keeps this dead load; the source shape that makes it unnecessary has not been found */
        unused = ((Struct800ABDC8 *)unused)->unk0C;
    }
    return 0;
}
