#include "common.h"

typedef void (*TownCallback)(void);

extern u8 D_8001CED4;
extern u8 D_8001CF1C;
extern u8 *D_8001E950;

/* Invoke one of two callbacks using the current state index. */
void func_8001CF44(void)
{
    TownCallback callbacks[2];

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    callbacks[0] = (TownCallback)&D_8001CED4;
    callbacks[1] = (TownCallback)&D_8001CF1C;
    callbacks[D_8001E950[1]]();
}

/* MECHANISM: A two-entry sibling stack array creates the retail 0x20 frame
   and 0x10/0x14 callback slots; a body-entry scheduling fence retains the
   compiler-generated ra save at word 1. The callback's void ABI emits no args. */
