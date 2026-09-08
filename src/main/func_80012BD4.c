#include "common.h"

extern s32 func_80021D54(s32 arg0);
extern s32 func_80023FF0(void *arg0, s32 arg1);
extern void func_80023004(void *arg0);
extern void func_80025B9C(void);
extern void func_80024F7C(void);
extern void func_80025B60(void);

/* Processes the current slot and selects callbacks when unavailable or all five are done. */
void func_80025BD4(void *state_arg) {
    void *state;
    s32 slot;

    state = state_arg;
    slot = *(s32 *)((u8 *)state + 0x24);
    if (slot < 5) {
        if (func_80021D54(slot) != 0) {
            *(s32 *)((u8 *)state + 4 + slot * 4) = func_80023FF0((u8 *)state - 0x20, slot);
            *(s32 *)((u8 *)state + 0x24) = *(s32 *)((u8 *)state + 0x24) + 1;
        } else {
            *(void (**)(void))((u8 *)state + 0x34) = func_80025B9C;
            func_80023004((u8 *)state - 0x20);
            *(void (**)(void))((u8 *)state - 0x10) = func_80024F7C;
        }
    }
    if (slot == 5) {
        *(void (**)(void))((u8 *)state - 0x10) = func_80025B60;
    }
}
