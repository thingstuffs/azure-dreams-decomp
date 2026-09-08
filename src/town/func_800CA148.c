#include "common.h"

extern s32 *func_8008FAC0(void *arg0, void *arg1);
extern void func_800C3780(void *arg0, void *arg1, s32 arg2);
extern void func_800C792C(void *arg0);
extern void func_800C7C3C(void *arg0, void *arg1, s32 arg2);
extern void func_800C7CAC(void *arg0, void *arg1, s32 arg2);

extern u8 D_800CFCB4[];
extern s32 D_80113220[];

void func_800C78A8(void *arg0, void *arg1, s32 arg2) {
    s32 *entry;
    s32 state;
    s32 timer;

    entry = func_8008FAC0(arg0, D_800CFCB4);
    if (entry != 0) {
        state = entry[0];
        if (state != 2) {
            if (state == 0) {
                ((s32 *)arg1)[0] -= entry[1];
                func_800C792C(entry);
                return;
            }
            if (state == 1) {
                ((s32 *)arg1)[1] -= entry[1];
            }
            func_800C7C3C(arg0, arg1, arg2);
            return;
        }
    }

    timer = --D_80113220[0];
    if (timer <= 0) {
        func_800C3780(arg0, arg1, arg2);
        func_800C7CAC(arg0, arg1, arg2);
        *(u16 *)((u8 *)arg1 + 2) = *(u16 *)((u8 *)arg0 + 0x84);
        *(u16 *)((u8 *)arg1 + 6) = *(u16 *)((u8 *)arg0 + 0x86);
        return;
    }

    *(u16 *)((u8 *)arg1 + 2) +=
        ((s16)*(u16 *)((u8 *)arg0 + 0x84) -
         *(s16 *)((u8 *)arg1 + 2)) / timer;
    *(u16 *)((u8 *)arg1 + 6) +=
        ((s16)*(u16 *)((u8 *)arg0 + 0x86) -
         *(s16 *)((u8 *)arg1 + 6)) / timer;
}
