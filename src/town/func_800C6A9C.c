#include "common.h"
#include "shared/object_index_slots.h"

extern s32 D_800C3A98;
extern void func_800C2E84();

// Updates an object using its linked data, then resets its indexed flag and state.
void func_800C41FC(void *object, s32 unused, s32 updateValue) {
    void *objectData;

    objectData = *(void **)((u8 *)object + 0x80);
    func_800C2E84(object, updateValue, *(s32 *)((u8 *)objectData + 8));
    D_80082660[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = &D_800C3A98;
    *(s16 *)((u8 *)object + 0x6C) = 0x20;
}
