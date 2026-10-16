#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

void dungeonBeginDeferredItemAction(); /* extern */
void dungeonClearSlotAndUpdateLinkedState();                         /* extern */
void dungeonAdjustSourceValueAndFinalize();           /* extern */
s16 func_800A48F0();    /* extern */
void func_800A5F38();                 /* extern */
void func_800A63B8();            /* extern */
s32 dungeonApplyActorFoodPreference();            /* extern */
void dungeonCreateColoredEffectWithSound();    /* extern */
extern M2C_UNK D_800E206A;


/* Update entity state and counters, with special handling for the primary entity. */
s32 dungeonUseItemToApplySpeedBoost(void *entity, s32 event_id, s16 event_param) {
    u8 update_count;

    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = event_id;
        dungeonBeginDeferredItemAction(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, event_id, event_param);
        if (dungeonApplyActorFoodPreference(entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, event_id);
            return 1;
        }
    }
    update_count = (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 2));
    if (update_count < 0xFFU) {
        (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 2)) = (u8) (update_count + 1);
    }
    func_800A48F0(entity, 7, 8);
    if (((EntityRec *)entity)->flags14 & 0x4000) {
        dungeonAdjustSourceValueAndFinalize(entity, &D_800E206A);
    }
    dungeonCreateColoredEffectWithSound(entity - 0x20, 0xF02020, 0x616);
    dungeonClearSlotAndUpdateLinkedState(event_id);
    dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
    return 1;
}

