#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

extern M2C_UNK func_80033CD8();
extern M2C_UNK func_80033D08();
extern M2C_UNK func_800478B8();
extern s32 func_800644B8();
extern s32 func_8009D20C(void *, M2C_UNK);
extern M2C_UNK D_80045340;
extern s32 D_800814A0[3];

void func_8009E714(void *arg0, M2C_UNK arg1, void *arg2) {
    s32 state;
    s16 next;
    s32 scaled;
    s32 row;
    s32 value;

    state = func_8009D20C(arg0, arg1) == 1;
    if (func_8009D20C(arg0, arg1) == 1) {
        s8 *p = FIELD(arg0, s8 **, 0x98);
        if (p != 0) {
            *p = 0;
        }
        func_80033D08(arg0);
        FIELD(arg0, u16 *, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }
    if (state == 2) {
        func_80033D08(arg0);
        return;
    }
    func_80033CD8(arg0, &D_80045340);
    next = FIELD(arg0, u16 *, 0x6C) + 0x60;
    FIELD(arg0, u16 *, 0x6C) = next;
    scaled = func_800644B8(next);
    row = scaled >> 7;
    if (scaled < 0) {
        row = (scaled + 0x7F) >> 7;
    }
    value = (row + 0x20) * 0x30;
    if (value < 0) {
        value += 0x3F;
    }
    value >>= 6;
    FIELD(arg2, s8 *, 0xE) = (s8)value;
    FIELD(arg2, s8 *, 0xD) = (s8)value;
    FIELD(arg2, s8 *, 0xC) = (s8)value;
    if (!(FIELD(arg0, u16 *, -2) & 0x8000) &&
        FIELD(arg0, u8 *, 0x4D) == 0x13) {
        func_800478B8(arg2);
    }
}
