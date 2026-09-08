#include "common.h"

extern s16 D_80083780[];
extern u8 D_800C75D0[];
extern s8 D_800E3D20[];

/* Selects a nearby target, initializes its state slot, and returns change flags. */
s32 func_800C77D0(s32 slot_id, void *target, s32 target_id, s16 slot_value) {
    s32 distance;
    s32 target_coord;
    s32 change_flags;
    void *previous_target;
    u8 *state;
    u8 *slot;
    s32 new_target_id;

    distance = D_80083780[1];
    target_coord = *(s16 *)((u8 *)target + 2);
    distance -= target_coord;
    if (distance < 0) distance = -distance;
    if (distance >= 0xC1) {
        return 0;
    }
    new_target_id = target_id;
    ASM_KEEP(new_target_id);
    distance = D_80083780[3];
    target_coord = *(s16 *)((u8 *)target + 6);
    distance -= target_coord;
    if (distance < 0) distance = -distance;
    if (distance >= 0xC1) {
        return 0;
    }

    state = (u8 *)&D_80083178;
    slot = state + 0xB8;
    previous_target = *(void **)(slot + 0xC);
    *(s32 *)(slot + 0x34) = slot_id;
    *(void **)(slot + 0xC) = target;
    *(s32 *)(slot + 0x28) = 0;
    *(void **)slot = slot + 4;
    change_flags = previous_target != target;
    if (*(s32 *)(slot + 0x14) != 9) change_flags |= 2;
    *(s32 *)(slot + 0x14) = 9;
    *(s32 *)(slot + 0x18) = 0;
    *(s16 *)(slot + 0x26) = slot_value;
    *(void **)(state + 0xB4) = D_800C75D0;
    if (change_flags & 1) D_800E3D20[0] = new_target_id;
    *(s16 *)(slot + 0x24) = target_id;
    return change_flags;
}
