#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern u8 D_800E12A9[];

extern void dungeonBeginModeSelectedItemAction(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 dungeonProcessRecordAndUpdateLinkedState(s32, s32);
extern void dungeonClearSlotAndUpdateLinkedState(s32);
extern void func_800997FC(void *, s32, s16);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 dungeonApplyActorFoodPreference(void *, s32, s32);

/* Applies a value according to the target and mode, then updates bookkeeping. */
s32 dungeonUseItemToRevealItems(EntityRec *target, s32 value, s16 mode, s32 context)
{
    if (mode == 13) {
        return dungeonProcessRecordAndUpdateLinkedState(value, context);
    }

    if (target == ((u8 *)D_800E3D7C)) {
        target->unk_110 = value;
        dungeonBeginModeSelectedItemAction(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, value, mode);
        if (dungeonApplyActorFoodPreference(target,
                          D_800DDE84[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3,
                          value) == 0) {
            func_800A5F38(target, value);
            return 1;
        }
    } else {
        func_800997FC(D_800E12A9, context, mode);
        D_800E296C |= 0x200;
    }

    dungeonStatus.unk_0A--;
    dungeonClearSlotAndUpdateLinkedState(value);
    return 1;
}
