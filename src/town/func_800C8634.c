#include "common.h"
#include "shared/object_index_slots.h"

extern void func_800C2E84(void *state, s32 output, void *p);
extern void func_800C6270(s32 position);
extern u8 D_800C5D38;
extern u8 D_800D5598;

// Sets up an object, clears its indexed flag, assigns its state pointer, and runs the follow-up update.
void func_800C5D94(void *object, s32 followupValue, s32 setupValue) {
    func_800C2E84(object, setupValue, &D_800D5598);
    *(((*(s32 *)((u8 *)object + 0x60)) * 8) + ((u8 *)D_80082660)) = 0;
    *(u8 **)((u8 *)object + 0x54) = &D_800C5D38;
    func_800C6270(followupValue);
}
