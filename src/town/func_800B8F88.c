#include "common.h"

extern void func_800B65D8(s32 arg0, s16 arg1);
extern void func_800B6508(void *arg0);
extern s32 D_800B6578[];

/* Advance the object's five-step sequence, then reset it and set its next handler. */
void func_800B66E8(void *object) {
    s16 step;

    step = *(s16 *)((u8 *)object + 0xE);
    if (step < 5) {
        func_800B65D8(*(s32 *)((u8 *)object + 0x98), step);
        *(u16 *)((u8 *)object + 0xE) = *(u16 *)((u8 *)object + 0xE) + 1;
        return;
    }
    func_800B6508(object);
    *(void **)object = &D_800B6578[0];
}
