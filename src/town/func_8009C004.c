#include "common.h"

extern u8 D_80082660[];
extern u8 D_800D05E0[];

/* Initializes the object state and registers its enclosing record globally. */
void func_80099764(void *object) {
    u8 *global_state;

    *(void **)((u8 *)object + 0x44) = D_800D05E0;
    *(s32 *)((u8 *)object + 0x40) = 1;
    global_state = D_80082660;
    *(void **)(global_state + 0xC) = (u8 *)object - 0x20;
    global_state[8] = 0;
}
