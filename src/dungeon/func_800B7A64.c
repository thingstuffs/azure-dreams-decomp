#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef struct DungeonObject {
    u8 pad00[5];
    u8 counter;
    u8 pad06[13];
    u8 kind;
    s32 flags;
    u8 pad18[0x10];
    u8 current;
    u8 limit;
    u8 pad2a[0x3a];
    s16 amount;
    u8 pad66[0xaa];
    u8 *payload;
} DungeonObject;

extern u8 D_80089354[];
extern u8 D_800E0E14[];
extern u8 D_800E0E34[];
extern u8 D_800E0E50[];

extern s32 func_8003AD08(s16, s32);
extern void func_80041E70(DungeonObject *);
extern void dungeonBeginDeferredItemAction(DungeonObject *, u8 *, u8 *, DungeonObject *);
extern void dungeonClearSlotAndUpdateLinkedState(u8 *);
extern s32 func_800990FC(void);
extern s32 func_80099194(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 func_80099734(void *record, u8 *out);
extern void func_800A5720(s8 *text);
extern void func_800A5F38(DungeonObject *, u8 *);
extern void func_800A63B8(DungeonObject *, u8 *, s16);
extern s32 func_800A6D30(void);
extern s32 dungeonCapPendingActorValueDelta(DungeonObject *);
extern s32 dungeonApplyActorFoodPreference(DungeonObject *, u32, s32);
extern void createActorValuePopup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern void dungeonCreateTimedPairedParticleEmitter(s32, s32, DungeonObject *);

/* Applies an item effect, selects its amount, and displays the result. */
s32 dungeonUseRandomHealingItem(DungeonObject *obj, u8 *payload, s16 effect_arg) {
    s16 effect_state;
    s32 amount;
    s16 remaining;
    u8 counter;
    s32 message_handle;
    s32 message_arg;
    const void *message;
    u16 *kind_flags;

    effect_state = 0;
    if (obj == (DungeonObject *)((u8 *)D_800E3D7C)) {
        obj->payload = payload;
        dungeonBeginDeferredItemAction(obj, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), obj);
        return 0;
    }
    if ((u32)obj <= 0x9FFFFFFFU) {
        func_800A63B8(obj, payload, effect_arg);
        kind_flags = D_800DDE84;
        if (dungeonApplyActorFoodPreference(obj, ((u32)kind_flags[obj->kind] >> 6) & 3, 0) == 0) {
            func_800A5F38(obj, payload);
            return 1;
        }
    }
    dungeonCreateTimedPairedParticleEmitter(*(s32 *)((u8 *)obj - 0x18), 0x20E020, obj);
    amount = (func_800A6D30() & 7) + 0x20;
    if (amount >= 0x100) {
        amount = 0xFF;
    }
    obj->amount = amount;
    if (obj->current == obj->limit) {
        effect_state = -1;
        if (*payload == 0xF) {
            counter = obj->counter;
            if (counter < 0xFFU) {
                obj->counter = counter + 1;
                func_80041E70(obj);
            }
            obj->amount = 1;
            effect_state = 1;
        }
    } else {
        remaining = obj->limit - obj->current;
        if (remaining < amount) {
            amount = remaining;
        }
        obj->amount = amount;
    }

    if (dungeonCapPendingActorValueDelta(obj) != 0) {
        s32 display_mode;

        display_mode = 0x10;
        if ((effect_state << 16) > 0) {
            display_mode = 0x8010;
        }
        createActorValuePopup(display_mode, obj, obj->amount, 1);
    }
    if (obj->flags & 0x4000) {
        message_handle = func_800990FC();
        if (effect_state > 0) {
            func_80099290(func_80099194(&D_80089354[0], func_8003AD08(obj->amount, func_80099194(&D_800E0E14[0],
                func_80099734(obj, message_handle)))));
        } else if (effect_state == 0) {
            func_80099290(func_80099194(&D_80089354[0], func_8003AD08(obj->amount, func_80099194(&D_800E0E34[0],
                func_80099734(obj, message_handle)))));
        } else {
            func_80099290(func_80099194(&D_800E0E50[0], message_handle));
        }
        func_800A5720(message_handle);
    }
    dungeonClearSlotAndUpdateLinkedState(payload);
    {
        DungeonGlobalStatus *counter_base;

        counter_base = &dungeonStatus;
        counter_base->unk_0A = ((u16)counter_base->unk_0A) - 1;
    }
    return 1;
}
