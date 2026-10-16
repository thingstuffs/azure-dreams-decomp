#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern u8 D_800E11FD[];

extern void dungeonBeginModeSelectedItemAction(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 dungeonProcessRecordAndUpdateLinkedState(s32, s32);
extern void dungeonClearSlotAndUpdateLinkedState(s32);
extern void func_800997FC(void *, s32, s16);
extern void dungeonPackAndSubmitCellHeightLevels(void);
extern void func_800A56E0(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 dungeonApplyActorFoodPreference(void *, s32, s32);

/* Applies an item to the target and removes it when consumed. */
s32 dungeonUseItemToRevealFloorMap(EntityRec *target, s32 item, s16 target_kind, s32 target_data)
{
    if (target_kind == 13) {
        return dungeonProcessRecordAndUpdateLinkedState(item, target_data);
    }

    if (target == ((u8 *)D_800E3D7C)) {
        target->unk_110 = item;
        dungeonBeginModeSelectedItemAction(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, item, target_kind);
        if (dungeonApplyActorFoodPreference(target,
                          D_800DDE84[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3,
                          item) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
    } else {
        func_800997FC(D_800E11FD, target_data, target_kind);
        dungeonPackAndSubmitCellHeightLevels();
        D_800E296C |= 0x800000;
        func_800A56E0(0x80F);
    }

    dungeonStatus.unk_0A--;
    dungeonClearSlotAndUpdateLinkedState(item);
    return 1;
}
