#include "common.h"

extern void func_8004DD2C(s32 arg0);
extern void func_80053DA8(s32 arg0);
extern void func_800AD7F8(void *arg0);
extern void func_800AD8CC(void *arg0);
extern s32 func_800AD99C(void *arg0);
extern void func_800AE30C(void *arg0);
extern void func_800B17E4(s32 arg0);

extern s32 D_800D1558;
extern s32 D_800D155C;

/* Handles the selected entry according to its type, flags, and availability. */
void func_800ADA1C(s32 *state) {
    u8 *selected_entry;

    selected_entry = (u8 *) (state[1] * 4 + state[8]);
    if (selected_entry[1] != 0x16) {
        if (!(selected_entry[3] & 0x80)) {
            if (func_800AD99C(state) != 0) {
                func_80053DA8(0x503);
                func_800AD7F8(state);
                func_800B17E4(state[10]);
                return;
            }
            func_80053DA8(0x506);
            func_8004DD2C(D_800D1558);
            return;
        }
        func_80053DA8(0x506);
        if (state[6] == 1) {
            func_8004DD2C(D_800D155C);
            return;
        }
    } else {
        func_800AE30C((s8 *) state - 0x20);
        func_800AD8CC(state);
    }
}
