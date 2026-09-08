#include "common.h"

typedef struct {
    s8 active;
    u8 pad1[3];
    void *object;
} ObjectSlot;

extern ObjectSlot D_80082660[];
extern void func_800C4174(void *arg0, s32 arg1, s32 arg2);

/* Store the object in its slot, mark the slot inactive, and call the next handler. */
void func_800CCA18(void *object, s32 callback_arg1, s32 callback_arg2) {
    s32 slot_index;

    slot_index = *(s32 *)((u8 *)object + 0x60);
    D_80082660[slot_index].object = (u8 *)object - 0x20;
    D_80082660[*(s32 *)((u8 *)object + 0x60)].active = 0;
    func_800C4174(object, callback_arg1, callback_arg2);
}
