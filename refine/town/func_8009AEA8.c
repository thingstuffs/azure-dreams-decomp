#include "common.h"

extern void func_80099754(void *);
extern u8 D_80098544[8];

/* Ease the object's value toward -0x800000 until the timer expires, then advance the state. */
void func_80098608(void *state, void *object) {
    u16 ticks_left;
    s32 current_value;

    ticks_left = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = ticks_left;
    if ((ticks_left << 16) > 0) {
        current_value = *(s32 *)((u8 *)object + 8);
        current_value += ((s32)0xFF800000 - current_value) / 2;
        *(s32 *)((u8 *)object + 8) = current_value;
        return;
    }

    *(s32 *)((u8 *)object + 8) = (s32)0xFF800000;
    func_80099754(object);
    *(u16 *)((u8 *)state + 0xA) = 10;
    *(void **)((u8 *)state + 4) = D_80098544;
}
