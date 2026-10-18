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
extern void begin_deferred_item_action(DungeonObject *, u8 *, u8 *, DungeonObject *);
extern void clear_slot_and_update_linked_state(u8 *);
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void apply_item_effect_at_entity_position(DungeonObject *, u8 *);
extern void display_item_status_message(DungeonObject *, u8 *, s16);
extern s32 generate_random_value(void);
extern s32 cap_pending_actor_value_delta(DungeonObject *);
extern s32 apply_actor_food_preference(DungeonObject *, u32, s32);
extern void create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern void create_timed_paired_particle_emitter(s32, s32, DungeonObject *);

/* Applies an item effect, selects its amount, and displays the result. */
s32 use_random_healing_item(DungeonObject *obj, u8 *payload, s16 effect_arg) {
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
        begin_deferred_item_action(obj, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), obj);
        return 0;
    }
    if ((u32)obj <= 0x9FFFFFFFU) {
        display_item_status_message(obj, payload, effect_arg);
        kind_flags = D_800DDE84;
        if (apply_actor_food_preference(obj, ((u32)kind_flags[obj->kind] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(obj, payload);
            return 1;
        }
    }
    create_timed_paired_particle_emitter(*(s32 *)((u8 *)obj - 0x18), 0x20E020, obj);
    amount = (generate_random_value() & 7) + 0x20;
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

    if (cap_pending_actor_value_delta(obj) != 0) {
        s32 display_mode;

        display_mode = 0x10;
        if ((effect_state << 16) > 0) {
            display_mode = 0x8010;
        }
        create_actor_value_popup(display_mode, obj, obj->amount, 1);
    }
    if (obj->flags & 0x4000) {
        message_handle = get_unused_text_buffer();
        if (effect_state > 0) {
            func_80099290(expand_text_control_codes(&D_80089354[0], func_8003AD08(obj->amount, expand_text_control_codes(&D_800E0E14[0],
                append_entity_display_text(obj, message_handle)))));
        } else if (effect_state == 0) {
            func_80099290(expand_text_control_codes(&D_80089354[0], func_8003AD08(obj->amount, expand_text_control_codes(&D_800E0E34[0],
                append_entity_display_text(obj, message_handle)))));
        } else {
            func_80099290(expand_text_control_codes(&D_800E0E50[0], message_handle));
        }
        display_text_with_fullwidth_adjustment(message_handle);
    }
    clear_slot_and_update_linked_state(payload);
    {
        DungeonGlobalStatus *counter_base;

        counter_base = &g_dungeon_status;
        counter_base->unk_0A = ((u16)counter_base->unk_0A) - 1;
    }
    return 1;
}
