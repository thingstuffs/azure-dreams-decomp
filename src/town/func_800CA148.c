#include "common.h"

extern s32 *func_8008FAC0(void *arg0, void *arg1);
extern void func_800C3780(void *arg0, void *arg1, s32 arg2);
extern void func_800C7C3C(void *arg0, void *arg1, s32 arg2);
extern void func_800C7CAC(void *arg0, void *arg1, s32 arg2);

extern u8 D_800CFCB4[];
extern s32 D_80113220[];

/* Applies a motion offset or interpolates the position toward the object coordinates. */
void func_800C78A8(void *object, void *position, s32 update_arg) {
    s32 *motion_entry;
    s32 state;
    s32 frames_left;

    motion_entry = func_8008FAC0(object, D_800CFCB4);
    if (motion_entry != 0) {
        state = motion_entry[0];
        if (state != 2) {
            if (state == 0) {
                ((s32 *)position)[0] -= motion_entry[1];
            } else if (state == 1) {
                ((s32 *)position)[1] -= motion_entry[1];
            }
            func_800C7C3C(object, position, update_arg);
            return;
        }
    }

    frames_left = --D_80113220[0];
    if (frames_left <= 0) {
        func_800C3780(object, position, update_arg);
        func_800C7CAC(object, position, update_arg);
        *(u16 *)((u8 *)position + 2) = *(u16 *)((u8 *)object + 0x84);
        *(u16 *)((u8 *)position + 6) = *(u16 *)((u8 *)object + 0x86);
        return;
    }

    *(u16 *)((u8 *)position + 2) +=
        ((s16)*(u16 *)((u8 *)object + 0x84) -
         *(s16 *)((u8 *)position + 2)) / frames_left;
    *(u16 *)((u8 *)position + 6) +=
        ((s16)*(u16 *)((u8 *)object + 0x86) -
         *(s16 *)((u8 *)position + 6)) / frames_left;
}
