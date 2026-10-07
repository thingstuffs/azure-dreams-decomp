#include "common.h"

extern s32 D_800C3960;
s16 func_800C2BE8(void *object);
void func_800C4174(void *object, s32 update_context, s32 setup_context);

// Initialize the object's state and delegate the remaining setup.
void func_800C40D0(void *object, s32 update_context, s32 setup_context) {
    *(s8 *)((u8 *)object + 0x15) = 0;
    *(void **)((u8 *)object + 0x50) = &D_800C3960;
    *(s16 *)((u8 *)object + 0x72) = func_800C2BE8(object);
    func_800C4174(object, update_context, setup_context);
}
