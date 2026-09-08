#include "common.h"

extern void func_800C2E84(void *, s32, void *);
extern s32 func_800374F4(s32);
extern u8 D_800C9AD4[];
extern u8 D_800D6504[];

// Initialize the object's data, movement state, and variant.
void func_800C9CDC(void *object, void *movementState, s32 initializationValue) {
    func_800C2E84(object, initializationValue, D_800D6504);
    *(void **)((u8 *)object + 0x50) = D_800C9AD4;
    *(s32 *)((u8 *)movementState + 0x14) = 0xFFF60000;
    *(s16 *)((u8 *)object + 0x90) = (s16)(func_800374F4(3) + 1);
}
