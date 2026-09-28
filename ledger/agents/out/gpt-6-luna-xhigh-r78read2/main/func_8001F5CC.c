#include "common.h"

extern s32 func_80401E2C(s32 arg0);
extern s32 func_80404364(void *arg0, s32 arg1);
extern void func_8040325C(void *arg0);
extern void func_80406590(void);
extern void func_80405A3C(void);

/* Processes the current slot and selects callbacks when unavailable or all five are done. */
void func_804065CC(void *state_arg) {
    void *slot_state;
    s32 slot;

    slot_state = state_arg;
    slot = *(s32 *)((u8 *)slot_state + 0x24);
    if (slot < 5) {
        if (func_80401E2C(slot) != 0) {
            *(s32 *)((u8 *)slot_state + 4 + slot * 4) = func_80404364((u8 *)slot_state - 0x20, slot);
            *(s32 *)((u8 *)slot_state + 0x24) = *(s32 *)((u8 *)slot_state + 0x24) + 1;
        } else {
            *(void (**)(void))((u8 *)slot_state + 0x34) = func_80406590;
            func_8040325C((u8 *)slot_state - 0x20);
            *(void (**)(void))((u8 *)slot_state - 0x10) = func_80405A3C;
        }
    }
    if (slot == 5) {
        *(void (**)(void))((u8 *)slot_state - 0x10) = func_80406590;
    }
}
