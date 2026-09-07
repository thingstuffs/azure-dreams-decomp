#include "common.h"

extern s32 func_80049E1C(s32 arg0, s32 arg1, s32 arg2);
extern void func_80053DA8(s32 arg0);
extern void func_800AD8CC(s32 *arg0);
extern void func_800ADA1C(s32 *arg0);
extern void func_800ADB04(s32 *arg0);
extern void func_800ADBD4(void) __attribute__((noreturn));
extern void func_800AE30C(void *arg0);
extern void func_800B1778(s32 arg0, s32 arg1, s32 arg2);
extern void func_800B17C0(s32 arg0, s32 arg1);

extern s32 D_80082AB8;
extern s32 D_80083160[5];

void func_800ADB5C(s32 *arg0) {
    s32 *state;
    s32 input;
    s32 direction;
    s32 value;
    s32 quotient;

    state = D_80083160;
    input = state[2];
    direction = 0;
    if (input == 0) {
        return;
    }

    if (state[4] & 0x10) {
        func_80053DA8(0x514);
        func_800AD8CC(arg0);
        func_800ADBD4();
    }
    if (state[4] & 0x20) {
        func_80053DA8(0x515);
        D_80082AB8 = 0;
        func_800AE30C((s8 *)arg0 - 0x20);
        return;
    }
    if (state[4] & 0x40) {
        func_800ADA1C(arg0);
        return;
    }
    if (!(input & 0xF000)) {
        return;
    }

    if (state[4] & 0xF000) {
        arg0[5] = 0;
        if (state[4] & 0x8000) direction = -5;
        else if (state[4] & 0x2000) direction = 5;
        else if (state[4] & 0x1000) direction = -1;
        else if (state[4] & 0x4000) direction = 1;
    } else {
        if (arg0[5] >= 9) {
            if (input & 0x8000) direction = -5;
            else if (input & 0x2000) direction = 5;
            else if (input & 0x1000) direction = -1;
            else if (input & 0x4000) direction = 1;
            arg0[5] = *(volatile s32 *)&arg0[5] - 1;
        } else {
            arg0[5]++;
            return;
        }
    }

    value = func_80049E1C(arg0[1], direction, arg0[2]);
    quotient = value / 5;
    if (value == arg0[1]) {
        return;
    }

    func_80053DA8(0x502);
    arg0[1] = value;
    if (quotient != arg0[3]) {
        arg0[3] = quotient;
        func_800B1778(arg0[10], quotient, value);
    }
    func_800B17C0(arg0[10], value);
    if (state[2] & 0x40) {
        func_800ADA1C(arg0);
    }
    func_800ADB04(arg0);
}
