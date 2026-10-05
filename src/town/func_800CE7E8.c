#include "common.h"
#include "shared/object_index_slots.h"

extern void func_800C2E84(void *state, s32 output, void *entries);
extern u8 D_800CBFAC[];
extern u8 D_800D6A70[];

// Initialize the object, clear its state fields and indexed flag, and set its data pointer.
void func_800CBF48(void *object, s32 unused, s32 initValue) {
    func_800C2E84(object, initValue, D_800D6A70);
    D_80082660[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(s16 *)((u8 *)object + 0x68) = 0;
    *(s16 *)((u8 *)object + 0x6A) = 0;
    *(void **)((u8 *)object + 0x54) = D_800CBFAC;
    *(s16 *)((u8 *)object + 0x6C) = 0;
}
