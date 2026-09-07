#include "common.h"

extern u8 *D_80174710;
extern s32 D_800814A0;

extern void func_800A32A4(void *arg0);
extern void func_8009A3D0(s32 arg0, s32 arg1, s32 arg2);
extern void func_8009A028(void *arg0);

void func_81254248(void) {
    u8 **slot;
    u8 *obj;

    slot = &D_80174710;
    obj = *slot;
    if (obj != 0) {
        u8 *arg = obj + 0x20;
        u8 *data = *(u8 **)(obj + 0xC);
        s32 sound_x;
        s32 sound_y;
        s32 effect;

        func_800A32A4(arg);
        sound_x = data[0x24];
        sound_y = data[0x25];
        effect = 0x3000;
        if (*(u32 *)(arg + 0x1C) & 0x2000) {
            effect = 0x300;
        }
        func_8009A3D0(sound_x, sound_y, effect);
        func_8009A028(arg);
        *(u16 *)(arg - 2) |= 0x8000;
        *slot = 0;
        D_800814A0 |= 0x8000;
    }
}
