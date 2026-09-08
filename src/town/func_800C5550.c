#include "common.h"

extern s32 func_8003DB94();
extern s32 func_80047784(int, short, short);

/* Clear the object status byte and dispatch the target update using its mode byte. */
void func_800C2CB0(void *object, int target, int value, s16 flags) {
    *(s8 *)((s8 *)object + 0x92) = 0;
    if (*(u8 *)((s8 *)object + 0x93) == 0) {
        func_8003DB94(target, value, flags);
        return;
    } else {
        func_80047784(target, value, flags);
    }
}
