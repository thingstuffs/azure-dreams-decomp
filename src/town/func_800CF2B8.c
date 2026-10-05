#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 active;
    u8 pad1[3];
    void *object;
} ObjectSlot;

extern void func_800C4174(void *object, s32 update_context, s32 setup_context);

/* Store the object in its slot, mark the slot inactive, and call the next handler. */
void func_800CCA18(void *object, s32 callback_arg1, s32 callback_arg2) {
    s32 slot_index;

    slot_index = *(s32 *)((u8 *)object + 0x60);
    D_80082660[slot_index].object = (u8 *)object - 0x20;
    D_80082660[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    func_800C4174(object, callback_arg1, callback_arg2);
}
