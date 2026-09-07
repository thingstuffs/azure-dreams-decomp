#include "common.h"

extern void func_80044A50(void *arg0);
extern void func_800478B8();

extern s32 D_800814A0[3];
extern u8 D_80083160[0xAB];
extern s32 D_80175220;

void func_801749F4(u8 *arg0, void *arg1, u8 *arg2)
{
    s16 counter;
    u8 *state = D_80083160;

    if (arg0[0x9A] == 0) {
        D_80175220 = *(s32 *)(arg2 + 8);
        func_800478B8(arg2, arg1, state);
        if (*(u16 *)(arg2 + 0x14) & 0xE000) {
            func_80044A50(arg0 - 0x20);
            *(s16 *)(arg0 + 0x96) = 0x10;
            arg0[0x9A]++;
            return;
        }
    } else {
        state[0xA8] = (u8)(state[0xA8] +
            ((s32)(0x80 - state[0xA8]) / *(s16 *)(arg0 + 0x96)));
        state[0xA9] = (u8)(state[0xA9] +
            ((s32)(0x80 - state[0xA9]) / *(s16 *)(arg0 + 0x96)));
        state[0xAA] = (u8)(state[0xAA] +
            ((s32)(0x80 - state[0xAA]) / *(s16 *)(arg0 + 0x96)));

        counter = *(u16 *)(arg0 + 0x96) - 1;
        *(s16 *)(arg0 + 0x96) = counter;
        if (counter <= 0) {
            *(u16 *)(arg0 - 2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }
}
