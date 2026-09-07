#include "common.h"

#define FIELD(p, type, offset) (*(type *)((s8 *)(p) + (offset)))

extern void func_800422DC(void *arg0, void *arg1);
extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_80098B38(void *arg0);
extern void func_8009A028(void *arg0);
extern void func_8009A3D0(u8 arg0, u8 arg1, s32 arg2);
extern s16 func_800A1BD0(void *arg0);
extern void func_800A32A4(void *arg0);

extern s32 D_800E3D7C;
extern void *D_800E3DF0[];
extern s32 D_800814A0;

s16 func_800A6620(void *arg0, s32 arg1)
{
    s32 mode;
    s32 index;
    void **slot;
    void **table;
    void *object;
    void *entry;
    void *owner;
    u8 sound_x;
    u8 sound_y;

    table = D_800E3DF0;
    index = FIELD(arg0, u8, 3) & 0x1F;
    slot = &table[index];
    object = *slot;
    *slot = 0;
    index = FIELD(object, u8, 0x43);

    if (index < 0x40) {
        FIELD(object, u8, 0x44) = 0;
        func_800422DC((void *)(0x80010A80 + index * 0x54), object);
    }

    if (FIELD(arg0, u8, 3) & 0x20) {
        index = func_800A1BD0(object);
        if (index >= 0) {
            entry = (void *)(index * 4 + D_800E3D7C);
            FIELD(entry, s32, 0xAC) = 0;
            FIELD(entry, s32, 0xD0) = 0;
        }

        if ((func_80042900(object, 0x1B) << 16) == 0) {
            owner = FIELD(object, void *, -0x14);
            sound_x = FIELD(owner, u8, 0x24);
            sound_y = FIELD(owner, u8, 0x25);
            mode = 0x3000;
            if (FIELD(object, s32, 0x1C) & 0x2000) {
                mode = 0x300;
            }
            func_8009A3D0(sound_x, sound_y, mode);
        }

        if (arg1 != 0) {
            func_800A32A4(object);
        }
        func_8009A028(object);
        FIELD(object, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    func_80098B38(arg0);
    return index;
}
