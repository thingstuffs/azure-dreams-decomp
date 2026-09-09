#include "common.h"

extern void func_80035208();
extern void func_80099FDC();
extern void func_8009FAC4(s32, s32, s32, s32);
extern u16 D_80013714[8];
extern u8 D_800E045C[];
extern s32 D_800E3D7C;
extern s32 D_80175D50;

/* Reset state flags, relink the two attached objects, and submit the global buffer. */
void func_8016F200(s32 reset_arg_a, s32 reset_arg_b, s32 reset_arg_c, s32 reset_arg_d) {
    s32 object_index;
    s32 object;
    u8 *state;

    object_index = 0;
    state = (u8 *)(D_80175D50 + 0x20);
    *(u16 *)(state + 0x46) &= 0x7FFF;
    D_80013714[0] &= 0xFFF6;
    func_8009FAC4(reset_arg_a, reset_arg_b, reset_arg_c, reset_arg_d);
    state[0xAF] = 0;
    do {
        object = *(s32 *)((object_index * 4) + D_800E3D7C + 0xAC);
        if (object != 0) {
            func_80099FDC(object - 0x20);
        }
        object_index++;
    } while (object_index < 2);
    func_80035208(D_800E045C);
}
