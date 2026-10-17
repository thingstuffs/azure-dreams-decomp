#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef s32 M2C_UNK;

typedef struct {
    u8 pad_0[0xA];
    u16 field_A;
} D_80083460_Type;


void dungeonBeginDeferredItemAction();
void dungeonClearSlotAndUpdateLinkedState();
void dungeonAdjustSourceValueAndFinalize();
s32 lowerEntityLevel();
void func_800A5F38();
void func_800A63B8();
s32 dungeonApplyActorFoodPreference();
extern M2C_UNK D_800E173A;

/* Processes an entity's item interaction and consumes the item when finished. */
s32 dungeonUseItemToLowerLevel(EntityRec *entity, s32 item, s16 action) {
    if (entity == ((s32)D_800E3D7C)) {
        entity->unk_110 = item;
        dungeonBeginDeferredItemAction(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, item, action);
        if (dungeonApplyActorFoodPreference(
                entity,
                (D_800DDE84[(*(u8 *)((u8 *)&entity->unk_10 + 3))] >> 6) & 3,
                0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }
    if (lowerEntityLevel(entity, 1) == 0) {
        dungeonAdjustSourceValueAndFinalize(entity, &D_800E173A);
    }
    dungeonClearSlotAndUpdateLinkedState(item);
    {
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
    }
    return 1;
}
