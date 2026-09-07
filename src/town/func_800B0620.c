#include "common.h"

extern s32 func_80049E1C(s32 arg0, s32 arg1, s32 arg2);
extern void func_80053DA8(s32 arg0);
extern void func_800ADB30(void *arg0);
extern void func_800AE30C(void *arg0);
extern void func_800B1778(s32 arg0, s32 arg1, s32 arg2);
extern void func_800B17C0(s32 arg0, s32 arg1);
extern s32 D_80082AB8;
extern s32 D_80083160[5];

void func_800ADD80(s32 *arg0) {
    s32 *state;
    s32 input;
    s32 flags;
    s32 shift;
    s32 count;
    s32 value;
    s32 quotient;
    u8 *entry;
    state = D_80083160;
    input = state[2];
    shift = 0;
    if (input == 0) return;
    if (arg0[2] == 0) {
        if (state[4] & 0x20) {
            func_80053DA8(0x515); D_80082AB8 = 0;
            func_800AE30C((u8 *)arg0 - 0x20);
        }
        return;
    }
    flags = state[4];
    if (flags & 0x20) {
        func_80053DA8(0x515); D_80082AB8 = 0;
        func_800AE30C((u8 *)arg0 - 0x20); return;
    }
    if (flags & 0x40) {
        func_80053DA8(0x514); D_80082AB8 = 1;
        func_800AE30C((u8 *)arg0 - 0x20);
        entry = (u8 *)(arg0[1] * 4 + arg0[8]); entry[3] |= 0x20;
        return;
    }
    if (!(input & 0xF000)) return;
    if (state[4] & 0xF000) {
        *(volatile s32 *)&arg0[5] = 0;
        flags = *(volatile s32 *)&state[4];
        if (flags & 0x8000) shift = -5;
        else if (flags & 0x2000) shift = 5;
        else if (flags & 0x1000) shift = -1;
        else if (flags & 0x4000) shift = 1;
    } else {
        if (arg0[5] >= 9) {
            if (input & 0x8000) shift = -5;
            else if (input & 0x2000) shift = 5;
            else if (input & 0x1000) shift = -1;
            else if (input & 0x4000) shift = 1;
            count = *(volatile s32 *)&arg0[5]; arg0[5] = count - 1;
        } else {
            arg0[5]++; return;
        }
    }
    value = func_80049E1C(arg0[1], shift, arg0[2]);
    quotient = value / 5;
    if (value == arg0[1]) return;
    func_80053DA8(0x502); arg0[1] = value;
    if (quotient != arg0[3]) {
        arg0[3] = quotient; func_800B1778(arg0[10], quotient, value);
    }
    func_800B17C0(arg0[10], value); func_800ADB30(arg0);
}
