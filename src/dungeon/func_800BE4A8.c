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
void func_800A5F38();                 /* extern */
void func_800A63B8();            /* extern */
s32 dungeonApplyActorFoodPreference();            /* extern */
void dungeonCreateColoredEffectWithSound();    /* extern */
extern u8 D_800E1843[];


/* Process an entity event, increment its counter, and finish the event with a visual effect. */
s32 dungeonUseItemToIncreaseLuck(void *entity, s32 event, s16 event_type) {
    u8 entity_count;

    if (entity == ((s32)D_800E3D7C)) {
        ((EntityRec *)entity)->unk_110 = event;
        dungeonBeginDeferredItemAction(entity, ((M2C_UNK *)(&D_80083780)), ((M2C_UNK *)(&D_80082E80)), entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, event, event_type);
        if (dungeonApplyActorFoodPreference(entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, event);
            return 1;
        }
    }
    entity_count = (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 3));
    if (entity_count < 0xFFU) {
        (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 3)) = (u8) (entity_count + 1);
        if (((EntityRec *)entity)->flags14 & 0x4000) {
            dungeonAdjustSourceValueAndFinalize(entity, D_800E1843);
        }
    }
    dungeonCreateColoredEffectWithSound(entity - 0x20, 0x202020, 0x616);
    dungeonClearSlotAndUpdateLinkedState(event);

    dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
    return 1;
}
