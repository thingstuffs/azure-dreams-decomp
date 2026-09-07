#include "common.h"

extern s32 func_8009A350(s16 arg0, s16 arg1, s32 arg2, u16 *flags);
extern void func_8009B48C(void);
extern s32 func_800A41F0(void *object);
extern void *D_800E3D7C[];

void *func_8009B390(s16 arg0, s16 arg1, s16 arg2)
{
    u16 flags;
    s32 difference;
    void *head;
    void *position;
    void *tile;

    if ((func_8009A350((u16)(arg0 - 1), arg1, 0, &flags) << 16) == 0) {
        return 0;
    }
    if (!(flags & 0x3300)) {
        func_8009B48C();
        return 0;
    }

    position = D_800E3D7C[0];
    head = position;
    do {
        tile = *(void **)((u8 *)position - 0x14);
        if (*(u8 *)((u8 *)tile + 0x24) == (u16)arg0 &&
            *(u8 *)((u8 *)tile + 0x25) == (u16)arg1) {
            difference = *(s16 *)((u8 *)position + 0x88) - arg2;
            if (difference < 0) {
                difference = -difference;
            }
            if (difference < 0x40 &&
                (func_800A41F0(position) << 16) != 0) {
                return position;
            }
        }
        position = (u8 *)*(void **)((u8 *)position + 0x5C) + 0x20;
    } while (position != head);
    return 0;
}
