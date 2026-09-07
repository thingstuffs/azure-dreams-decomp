#include "common.h"

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784();
extern s16 D_80083228[5];
extern u8 D_80175E9C[];
extern u8 D_80175EA4[];
extern u8 D_80175EAC[];

void func_80173678(void *arg0, s32 arg1, void *arg2, void *arg3) {
    s32 kind;
    u8 *data;
    u8 *old;

    FIELD(arg0, s8, 0x9A) = 0x10;
    FIELD(arg0, s8, 0x9B) = 0;
    kind = FIELD(arg3, u8, 0x48);
    if (kind == 0xE) {
        goto case_14;
    }
    if ((s32) kind < 0xF) {
        if (kind == 0xD) {
            goto case_13;
        }
        return;
    }
    if (kind == 0xF) {
        goto case_15;
    }
    return;

case_13:
    data = D_80175E9C;
    old = FIELD(arg2, u8 *, 0x2C);
    if (old == data) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = data;
    func_80047784(arg2,
                  data[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                  0);
    return;
case_14:
    data = D_80175EA4;
    old = FIELD(arg2, u8 *, 0x2C);
    if (old == data) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = data;
    func_80047784(arg2,
                  data[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                  0);
    return;
case_15:
    data = D_80175EAC;
    old = FIELD(arg2, u8 *, 0x2C);
    if (old == data) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = data;
    func_80047784(arg2,
                  data[((D_80083228[0] + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                  0);
}
