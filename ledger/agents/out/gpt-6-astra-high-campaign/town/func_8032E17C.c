#include "common.h"

extern u8 D_80016000[0x10];
extern s32 D_8001C368[];

/* Store the step count and advance the state counter by twice that count plus one. */
void func_8001897C(s32 step_count) {
    register void *root ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *state;
    s32 counter;

    root = *(void **)D_80016000;
    state = *(void **)((s8 *)root + 0x40);
    D_8001C368[0] = step_count;
    ASM_KEEP(root);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    counter = *(s32 *)((s8 *)state + 0x110);
    counter = counter + 1;
    counter = counter + (step_count * 2);
    *(s32 *)((s8 *)state + 0x110) = counter;
}
