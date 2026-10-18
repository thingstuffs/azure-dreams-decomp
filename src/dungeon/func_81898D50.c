#include "modules/dungeon_ovl_18b8824.h"

void mark_owner_on_target_completion(void *object_ref, s32 unused, void *target) {
    u8 *object;

    object = *(u8 **)((u8 *)object_ref + 0x0);
    *(u16 *)(object + 0x14) += 1;
    func_800478B8(target);
    if (*(u16 *)((u8 *)target + 0x14) & 0x6000) {
        *(u16 *)((u8 *)object_ref - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
