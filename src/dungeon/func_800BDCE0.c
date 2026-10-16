#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void func_80042B68(void *, s32);
extern void dungeonBeginModeSelectedItemAction(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 dungeonProcessRecordAndUpdateLinkedState(s32, s32);
extern void dungeonClearSlotAndUpdateLinkedState(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 dungeonAppendTypedFormattedValue(void *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s8 *text);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32);
extern s32 dungeonApplyActorFoodPreference(void *, s32, s32);
extern void dungeonCreateViewColorFlash(s32, s16);

extern u8 D_800E1756[];
extern u8 D_800E176F[];
extern u8 D_800E1788[];

/* Applies a curse-removal item effect and reports changes to equipped items. */
s32 dungeonUseItemToClearEquipmentFlags(void *target, s32 item, s16 use_mode, s32 use_context)
{
    u8 *equipment;
    s32 message_buf;
    s32 uncursed;

    if (use_mode == 13) {
        return dungeonProcessRecordAndUpdateLinkedState(item, use_context);
    }

    if (target == ((u8 *)D_800E3D7C)) {
        *(s32 *)((u8 *)target + 0x110) = item;
        dungeonBeginModeSelectedItemAction(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, item);
        if (dungeonApplyActorFoodPreference(target,
                          D_800DDE84[((u8 *)target)[0x13]] & 3,
                          item) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
    } else {
        dungeonCreateViewColorFlash(0xC0C0C0, 0);
        func_800A56E0(0x702);
        func_80042B68(target, 8);

        uncursed = 0;
        equipment = *(u8 **)(((u8 *)D_800E3D7C) + 0x4C);
        if (equipment[1] != 0 && (equipment[3] & 0x40) != 0) {
            equipment[3] &= 0xBF;
            message_buf = func_800990FC();
            func_80099290(func_80099194(D_800E1756,
                                        dungeonAppendTypedFormattedValue(equipment, message_buf)));
            func_800A5720(message_buf);
            uncursed = 1;
        }

        equipment = *(u8 **)(((u8 *)D_800E3D7C) + 0x50);
        if (equipment[1] != 0 && (equipment[3] & 0x40) != 0) {
            equipment[3] &= 0xBF;
            message_buf = func_800990FC();
            func_80099290(func_80099194(D_800E176F,
                                        dungeonAppendTypedFormattedValue(equipment, message_buf)));
            func_800A5720(message_buf);
            uncursed = 1;
        }

        if (uncursed == 0) {
            message_buf = func_800990FC();
            func_80099290(func_80099194(D_800E1788, message_buf));
            func_800A5720(message_buf);
        }
    }

    dungeonStatus.unk_0A--;
    dungeonClearSlotAndUpdateLinkedState(item);
    return 1;
}
