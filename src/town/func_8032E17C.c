#include "common.h"

extern u8 D_80016000[0x10];
extern s32 D_8001C368[];

/* Store the step count and advance the state counter by twice that count plus one. */
void func_8001897C(s32 step_count) {
    void *root;
    void *state;
    s32 counter;

    do {
        root = *(void **)D_80016000;
    } while (0);
    state = *(void **)((s8 *)root + 0x40);
    D_8001C368[0] = step_count;
    ASM_KEEP(root);
    counter = *(s32 *)((s8 *)state + 0x110);
    counter = counter + 1;
    counter = counter + (step_count * 2);
    *(s32 *)((s8 *)state + 0x110) = counter;
}
