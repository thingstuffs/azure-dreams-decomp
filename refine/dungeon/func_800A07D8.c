#include "common.h"

extern s32 func_8004A658(u8, u8);
extern void func_80098B38(void *);
extern void func_800A56E0(s32);
extern void func_800A7A7C(u16, u16, s16, s32, void *);
extern s16 D_80083460[];

/* Processes a target using the linked object's position, then decrements the shared count. */
void func_800A5F38(void *object_context, void *target) {
    void *object;

    object = *(void **)((s8 *)object_context - 0x18);
    func_800A7A7C(*(u16 *)((s8 *)object + 2) >> 6,
                   *(u16 *)((s8 *)object + 6) >> 6,
                   *(s16 *)((s8 *)object + 0xA),
                   func_8004A658(*((u8 *)target + 1), *(u8 *)target), target);
    func_800A56E0(0x50C);
    func_80098B38(target);
    D_80083460[5]--;
}
