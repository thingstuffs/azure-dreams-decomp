#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern s32 dungeonBeginModeSelectedItemAction();
extern s32 dungeonProcessRecordAndUpdateLinkedState();
extern void dungeonClearSlotAndUpdateLinkedState();
extern s32 func_800990FC();
extern s32 func_80099194();
extern void func_80099290();
extern void func_800A5720();
extern void func_800A5F38();
extern void func_800A6480();
extern s32 dungeonApplyActorFoodPreference();
extern void dungeonCreateViewColorFlash();

extern u8 D_800E1567[];
extern u8 D_800E3648[];


/* Apply an entity event or mark eligible slots, then finish the event. */
s32 dungeonMakeFloorTrapsInvisible(EntityRec *entity, s32 event, s16 event_type, s32 event_arg) {
    s32 message_arg;
    u8 *slot;
    u8 *event_state;
    u16 *pending_count;
    s32 message_buf;
    s32 message_end;
    s32 slot_index;

    if (event_type == 0xD) {
        return dungeonProcessRecordAndUpdateLinkedState(event, event_arg);
    }
    if (entity == ((u8 *)D_800E3D7C)) {
        entity->unk_110 = event;
        dungeonBeginModeSelectedItemAction(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A6480(entity, event);
        if (dungeonApplyActorFoodPreference(
                entity,
                D_800DDE84[(*(u8 *)((u8 *)&entity->unk_10 + 3))] & 3,
                event) == 0) {
            func_800A5F38(entity, event);
            return 1;
        }
    } else {
        dungeonCreateViewColorFlash(0xC02020, 1);
        message_buf = func_800990FC();

        message_arg = message_buf;
        if (D_80082E80.unk_026 >= 0) {
            for (slot_index = 0; slot_index < 0x20; slot_index++) {
                slot = &D_800E3648[slot_index * 4];
                if (slot[1] != 0 && slot[0] != 0) {
                    if (!(slot[3] & 0x40)) {
                        slot[3] |= 0x80;
                    }
                }
            }

            func_80099290(message_arg);
        } else {
            message_end = func_80099194(D_800E1567, message_buf);
            func_80099290(message_end);
        }
        func_800A5720(message_buf);
    }
    event_state = (u8 *)&dungeonStatus.unk_00;
    pending_count = (u16 *)(event_state + 0xA);
    *pending_count = *pending_count - 1;
    dungeonClearSlotAndUpdateLinkedState(event);
    return 1;
}
