#include "common.h"

extern s32 func_800478B8();
extern s32 D_800814A0[3];

/* Updates the target and records object counts and flags from its status. */
void func_8002457C(void *object_slot, void *unused, void *target)
{
    void *post_object;
    void *pre_object;

    pre_object = *(void **)object_slot;
    *(u16 *)((u8 *)pre_object + 0x14) += 1;
    func_800478B8(target);
    if (*(u16 *)((u8 *)target + 0x14) & 0x6000) {
        u16 object_count;
        u16 slot_flags;
        s32 global_flags;

        slot_flags = *(u16 *)((u8 *)object_slot - 2);
        post_object = *(void **)object_slot;
        *(u16 *)((u8 *)object_slot - 2) = slot_flags | 0x8000;
        global_flags = D_800814A0[0];
        object_count = *(u16 *)((u8 *)post_object + 0x18);
        D_800814A0[0] = global_flags | 0x8000;
        *(u16 *)((u8 *)post_object + 0x18) = object_count + 1;
    }
}
