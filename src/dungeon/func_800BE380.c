#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void dungeonBeginDeferredItemAction(void *, void *, void *, void *);
extern void dungeonClearSlotAndUpdateLinkedState(s32);
extern void dungeonAdjustSourceValueAndFinalize(void *, void *);
extern s32 func_800A48F0(void *, s32, s32);
extern void func_800A56E0(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 dungeonApplyActorFoodPreference(void *, s32, s32);

extern u8 D_800E1827[];

/* Applies the item's status effect to the target and consumes the handled item. */
s32 dungeonUseItemToApplySlow(void *target, s32 item, s16 use_kind)
{
    if (target == D_800E3D7C) {
        *(s32 *)((u8 *)target + 0x110) = item;
        dungeonBeginDeferredItemAction(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A63B8(target, item, use_kind);
        if (dungeonApplyActorFoodPreference(
                target, (D_800DDE84[*((u8 *)target + 0x13)] >> 6) & 3, 0) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
    }

    if ((func_800A48F0(target, 7, -10) << 16) != 0) {
        func_800A56E0(0x615);
        if (*(s32 *)((u8 *)target + 0x14) & 0x4000) {
            dungeonAdjustSourceValueAndFinalize(target, D_800E1827);
        }
    }

    dungeonClearSlotAndUpdateLinkedState(item);
    dungeonStatus.unk_0A--;
    return 1;
}
