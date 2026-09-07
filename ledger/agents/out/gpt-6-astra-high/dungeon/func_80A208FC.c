#include "common.h"

extern s32 D_800814A0[];
extern void func_800478B8(void *arg0);

/* Advances object motion, decrements its timer, and flags expiration. */
void func_801740FC(void *object_data, void *motion_data, void *work_data)
{
    s32 *motion = motion_data;
    u8 *object = object_data;
    u8 *work = work_data;
    s16 timer;

    *(s32 *)(work + 0xC) -= *(s32 *)(object + 0xA4);
    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];

    timer = *(u16 *)(object + 0x96) - 1;
    *(u16 *)(object + 0x96) = timer;
    if (timer <= 0) {
        *(u16 *)(object - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    func_800478B8(work);
}
