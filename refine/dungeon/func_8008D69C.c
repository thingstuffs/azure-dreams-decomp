#include "common.h"

extern s8 D_80083160[];
extern s32 D_80012090[];
extern s32 D_8008ACDC;

/* Waits for a countdown or global state change before resetting the object's handler. */
void func_80092DFC(void *object) {
    s8 *shared_data = D_80083160;
    u8 state = *(u8 *)((u8 *)object + 0x9B);
    u8 current_state;
    u16 timer;

    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    current_state = *(volatile u8 *)((u8 *)object + 0x9B);
    *(u16 *)((u8 *)object + 0x96) = 0x10;
    *(u8 *)((u8 *)object + 0x9B) = current_state + 1;
    return;

state_one:
    timer = *(u16 *)((u8 *)object + 0x96) - 1;
    *(u16 *)((u8 *)object + 0x96) = timer;
    if ((s16)timer < 0) {
        goto reset;
    }
    if (*(s32 *)(shared_data + 0x10) == 0) {
        return;
    }
    ASM_MEM_BARRIER();
    if (D_80012090[0] == state) {
        return;
    }

reset:
    *(s32 *)((u8 *)object + 0x124) = 0;
    *(void **)((u8 *)object + 0x8C) = &D_8008ACDC;
}
