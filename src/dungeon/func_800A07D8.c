#include "common.h"

extern s32 func_8004A658(u8, u8);
extern void func_80098B38(void *);
extern void func_800A56E0(s32);
extern void func_800A7A7C(u16, u16, s16, s32, void *);
extern s16 D_80083460[];

void func_800A5F38(void *arg0, void *arg1) {
    void *object;

    object = *(void **)((s8 *)arg0 - 0x18);
    func_800A7A7C(*(u16 *)((s8 *)object + 2) >> 6,
                   *(u16 *)((s8 *)object + 6) >> 6,
                   *(s16 *)((s8 *)object + 0xA),
                   func_8004A658(*((u8 *)arg1 + 1), *(u8 *)arg1), arg1);
    func_800A56E0(0x50C);
    func_80098B38(arg1);
    D_80083460[5]--;
}
