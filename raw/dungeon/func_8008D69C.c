#include "common.h"

extern s8 D_80083160[];
extern s32 D_80012090[];
extern s32 D_8008ACDC;
extern void func_80092E88(void *arg0, void *arg1) __attribute__((noreturn));

void func_80092DFC(void *arg0) {
    s8 *data = D_80083160;
    u8 state = *(u8 *)((u8 *)arg0 + 0x9B);
    u8 next_state;
    u16 timer;

    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    func_80092E88(arg0, data);

state_zero:
    next_state = *(volatile u8 *)((u8 *)arg0 + 0x9B);
    *(u16 *)((u8 *)arg0 + 0x96) = 0x10;
    *(u8 *)((u8 *)arg0 + 0x9B) = next_state + 1;
    func_80092E88(arg0, data);

state_one:
    timer = *(u16 *)((u8 *)arg0 + 0x96) - 1;
    *(u16 *)((u8 *)arg0 + 0x96) = timer;
    if ((s16)timer < 0) {
        goto reset;
    }
    if (*(s32 *)(data + 0x10) == 0) {
        return;
    }
    ASM_MEM_BARRIER();
    if (D_80012090[0] == state) {
        return;
    }

reset:
    *(s32 *)((u8 *)arg0 + 0x124) = 0;
    *(void **)((u8 *)arg0 + 0x8C) = &D_8008ACDC;
}

/* MECHANISM: The exact two-argument noreturn tail ABI lets LEAD 19 erase the false frame.
   A volatile block-local state reload fixes v0/v1 lifetimes; ASM_MEM_BARRIER preserves
   the required branch-delay nop and therefore both downstream branch displacements. */
