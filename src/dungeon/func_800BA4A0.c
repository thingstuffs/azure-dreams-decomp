#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern void func_80041E70(void *);
extern void dungeonBeginDeferredItemAction(void *, void *, void *, void *);
extern void dungeonClearSlotAndUpdateLinkedState(s32);
extern void dungeonAdjustSourceValueAndFinalize(void *, void *);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 dungeonApplyActorFoodPreference(void *, s32, s32);
extern void dungeonCreateColoredEffectWithSound(void *source, s32 color, unsigned short sound_id);

extern u8 D_800E1350[];


/* Handles an entity action, advancing capped counters and updating dungeon state. */
s32 dungeonUseItemToIncreaseAttack(void *entity, s32 action_id, s16 action_param)
{
    u32 progress_value;
    u8 progress;
    u8 completion_count;

    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = action_id;
        dungeonBeginDeferredItemAction(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, action_id, action_param);
        if (dungeonApplyActorFoodPreference(
                entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, action_id);
            return 1;
        }
    }

    if (((EntityRec *)entity)->unk_26 == ((EntityRec *)entity)->unk_68) {
        completion_count = (*(u8 *)&((EntityRec *)entity)->x);
        if (completion_count < 0xFF) {
            (*(u8 *)&((EntityRec *)entity)->x) = completion_count + 1;
            func_80041E70(entity);
        }
    }

    progress = ((EntityRec *)entity)->unk_26;
    progress_value = progress & 0xFF;
    if (progress_value < 0xFF && progress_value < ((EntityRec *)entity)->unk_68) {
        ((EntityRec *)entity)->unk_26 = progress + 1;
    }

    if (((EntityRec *)entity)->flags14 & 0x4000) {
        dungeonAdjustSourceValueAndFinalize(entity, D_800E1350);
    }
    dungeonCreateColoredEffectWithSound((u8 *)entity - 0x20, 0x2020F0, 0x616);
    dungeonClearSlotAndUpdateLinkedState(action_id);
    dungeonStatus.unk_0A--;
    return 1;
}
