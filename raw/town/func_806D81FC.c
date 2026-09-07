#include "common.h"

typedef struct {
    s8 pad[0x54];
    s32 (*callback)(s32);
} TownCallback;

typedef struct {
    s8 pad[0x20];
    TownCallback *callbacks;
} TownState;

extern TownState *D_80016000;
extern s8 D_80018AF8[];
extern u16 D_80019114;
extern s8 *D_80019118;

extern void func_80018548(s32);
extern void func_800185C0(s32);
extern s32 func_80018640(s32);

void func_800169FC(void) {
    D_80019118 = D_80018AF8;
    D_80019114 = 0;

    if (D_80016000->callbacks->callback(4) != 0) {
        func_800185C0(0x9AC);
    } else {
        func_80018548(0x9AC);
    }

    if (D_80016000->callbacks->callback(4) != 0) {
        func_800185C0(0x9AD);
    } else {
        func_80018548(0x9AD);
    }

    if ((func_80018640(0x9AC) != 0) &&
        (func_80018640(0x9AD) != 0)) {
        func_80018548(0x9AE);
    } else {
        func_800185C0(0x9AE);
    }

    func_800185C0(0x9B7);
    func_800185C0(0x9B8);
    func_800185C0(0x9B9);
    func_800185C0(0x9BA);
    func_80018548(0x9BB);
}

/* MECHANISM: The retail CFG uses three ordinary if/else joins, not early-return
   calls at the local jump targets. A typed callback chain rematerializes the
   global load for each call, leaving a 0x18 frame with only the ra save. */
