#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern void func_80042B68(void *entity, s32 value);
extern void dungeonBeginDeferredItemAction(void *entity_ptr, void *ptr0, void *ptr1, void *entity);
extern void dungeonClearSlotAndUpdateLinkedState(s32 event);
extern void func_800997FC(void *ptr);
extern void func_800A5F38(void *entity, s32 event);
extern void func_800A63B8(void *entity, s32 event, s16 event_type);
extern s32 dungeonApplyActorFoodPreference(void *entity, s32 value, s32 value2);
extern void dungeonCreateTimedPairedParticleEmitter(s32 value, s32 value2, void *entity);

extern u8 D_800E0E9B[];


typedef struct S_800BD72C_0_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_800BD72C_0_pre;   /* the 0x18 bytes before arg0 in dungeonUseItemToWakeActor, addressed as arg0[-1] */


/* Processes an entity event, handling the player separately and completing other events. */
s32 dungeonUseItemToWakeActor(void *entity, s32 event, s16 event_type)
{
    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = event;
        dungeonBeginDeferredItemAction(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }

    if ((s32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, event, event_type);
        if (dungeonApplyActorFoodPreference(
                entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, event);
            return 1;
        }
    }

    dungeonCreateTimedPairedParticleEmitter(((S_800BD72C_0_pre *)entity)[-1].unk_00, 0xC0C0C0, entity);
    if ((((EntityRec *)entity)->flags14 & 0x4000) &&
        !(((EntityRec *)entity)->flags1C & 0x200)) {
        func_800997FC(D_800E0E9B);
    }
    func_80042B68(entity, 1);
    dungeonClearSlotAndUpdateLinkedState(event);
    dungeonStatus.unk_0A--;
    return 1;
}
