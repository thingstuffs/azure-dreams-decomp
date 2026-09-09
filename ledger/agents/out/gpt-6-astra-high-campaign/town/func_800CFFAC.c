#include "common.h"

extern s32 func_800C30E0(void *arg0, void *arg1, s32 arg2);
extern s32 func_800644B8(s32 angle);
extern s32 func_80064584(s32 angle);
extern s32 *func_8008FAC0(void *arg0, void *arg1);
extern void func_800CDD98(void *arg0, void *arg1, s32 arg2);

extern u8 D_800CFCB4[];

#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S32_AT(p, off) (*(s32 *)((u8 *)(p) + (off)))

/* Update the object's orbit, apply a movement offset, and advance its timed state. */
void func_800CD70C(void *object, void *position, s32 update_arg) {
    s32 *motion_entry;
    s32 axis;
    u16 angle;
    u16 timer;

    if (func_800C30E0(object, position, update_arg) != 0) {
        return;
    }

    angle = U16_AT(object, 0x86);
    U16_AT(object, 0x86) = angle + 0x40;
    S16_AT(object, 0x72) = angle + 0x440;

    U16_AT(position, 2) = U16_AT(object, 0x84) +
        func_800644B8(S16_AT(object, 0x86)) / (0x1000 / S16_AT(object, 0x84));
    U16_AT(position, 6) = U16_AT(object, 0x86) +
        func_80064584(S16_AT(object, 0x86)) / (0x1000 / S16_AT(object, 0x84)) -
        U16_AT(object, 0x84);

    motion_entry = func_8008FAC0(object, D_800CFCB4);
    if (motion_entry != 0 && (axis = motion_entry[0]) != 2) {
        if (axis == 0) {
            S32_AT(position, 0) -= motion_entry[1];
        } else {
            S32_AT(position, 4) -= motion_entry[1];
        }
    } else {
        timer = U16_AT(object, 0x6C) - 1;
        U16_AT(object, 0x6C) = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
    }
    func_800CDD98(object, position, update_arg);
}
