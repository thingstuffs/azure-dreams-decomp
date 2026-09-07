#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

extern s32 func_800DC724();
extern s32 func_800DC82C();
extern s16 D_8008146C[];
extern void *D_800814A8;

void func_800DC988(void *arg0) {
    s16 value = D_8008146C[0];
    void *data = D_800814A8;
    void *state;

    FIELD(arg0, s32, 0x20) = ~value;
    state = (s8 *)arg0 + 0x20;
    FIELD(state, s32, 4) = ~FIELD(data, s32, 0xFC);
    FIELD(state, s32, 0x10) = ~FIELD(data, u8, 0x28);
    FIELD(state, s32, 0x14) = ~FIELD(data, u8, 0x29);
    FIELD(state, s32, 0x30) = ~FIELD(data, u8, 0x11);
    func_800DC82C(state);
    do {
        func_800DC724(state);
    } while (FIELD(state, s32, 0x58) != 0);
}
