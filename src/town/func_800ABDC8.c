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
    register s32 current_value ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register Struct800ABDC8 *current_object ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 x ASM_REG("$5");   /* UNRESOLVED C shape (pin): retail keeps this dead load in $a1; the source shape that makes it unnecessary has not been found */

    current_value = initial_value;
    current_object = (Struct800ABDC8 *)object;
    for (;;) {
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_800A9358(current_value);
        current_value = *(s32 *)((u8 *)current_object - 8);
        current_object = (Struct800ABDC8 *)((u8 *)current_value + 0x20);
        if (current_value == 0) {
            break;
        }
           /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        x = ((Struct800ABDC8 *)current_value)->unk08;
        ASM_KEEP(x);   /* UNRESOLVED C shape (pin): retail keeps this dead load; the source shape that makes it unnecessary has not been found */
        current_value = ((Struct800ABDC8 *)current_value)->unk0C;
    }
    return 0;
}
