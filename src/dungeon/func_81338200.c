#include "common.h"

extern void func_80035208();
extern void func_80099FDC();
extern void func_8009FAC4(s32, s32, s32, s32);
extern u16 D_80013714[8];
extern u8 D_800E045C[];
extern s32 D_800E3D7C;
extern s32 D_80175D50;

void func_8016F200(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 object;
    u8 *state;

    i = 0;
    state = (u8 *)(D_80175D50 + 0x20);
    *(u16 *)(state + 0x46) &= 0x7FFF;
    D_80013714[0] &= 0xFFF6;
    func_8009FAC4(arg0, arg1, arg2, arg3);
    state[0xAF] = 0;
    do {
        object = *(s32 *)((i * 4) + D_800E3D7C + 0xAC);
        if (object != 0) {
            func_80099FDC(object - 0x20);
        }
        i++;
    } while (i < 2);
    func_80035208(D_800E045C);
}
