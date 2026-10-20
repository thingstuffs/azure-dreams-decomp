#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef struct Entity {
    u8 pad[0x13];
    u8 unk_13;
    u32 flags;
    u8 pad2[0x110 - 0x18];
    s32 unk_110;
} Entity;

extern s32 D_80012090;
extern s16 D_8008146C;
extern u8 D_80089384[];
extern u8 D_800E15FE[];
extern u8 D_800E1677[];

s32 test_resident_bit(s32);
void begin_deferred_item_action(Entity *, void *, void *, Entity *);
void clear_slot_and_update_linked_state(s32);
s32 get_unused_text_buffer(void);
s32 expand_text_control_codes(u8 *src, u8 *dst);
void func_80099290(s8 *byte_ptr);
s32 append_typed_formatted_value(s32, s32);
s32 append_entity_display_text(void *record, u8 *out);
void display_formatted_context_message(void *);
void display_text_with_fullwidth_adjustment(s8 *text);
void apply_item_effect_at_entity_position(Entity *, s32);
void display_item_status_message(Entity *, s32, s16);
s32 create_return_magic_effect(Entity *);

/* Handles an item's effect on an entity and updates the pending action count. */
s32 use_return_magic(Entity *entity, s32 item, s16 action_type) {
    if (entity == ((Entity *)D_800E3D7C)) {
        entity->unk_110 = item;
        begin_deferred_item_action(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }
    if (entity->flags & 0x4000) {
        if ((u32)(entity->unk_13 - 3) < 0x2B) {
            if (D_80012090 == 0 && D_8008146C == 0x28 && test_resident_bit(0xA2) == 0) {
                DungeonGlobalStatus *counter;
                display_formatted_context_message(D_800E15FE);
                counter = &g_dungeon_status;
                (*(u16 *)&counter->unk_0A)--;
                clear_slot_and_update_linked_state(item);
                return 1;
            }
            if (create_return_magic_effect(entity) != 0) {
                DungeonGlobalStatus *counter;
                clear_slot_and_update_linked_state(item);
                counter = &g_dungeon_status;
                (*(u16 *)&counter->unk_0A)--;
                return 1;
            }
            return 0;
        }
        {
            s32 original_value;
            s32 current_value;
            s32 adjusted_value;

            adjusted_value = append_entity_display_text(entity, current_value = get_unused_text_buffer());
            original_value = current_value;
            current_value = adjusted_value;
            func_80099290(expand_text_control_codes(D_80089384, append_typed_formatted_value(item, expand_text_control_codes(D_800E1677, current_value))));
            display_text_with_fullwidth_adjustment(original_value);
            apply_item_effect_at_entity_position(entity, item);
        }
        return 1;
    }
    if ((u32)(entity->unk_13 - 3) < 0x2B) {
        if (create_return_magic_effect(entity) != 0) {
            DungeonGlobalStatus *counter = &g_dungeon_status;
            (*(u16 *)&counter->unk_0A)--;
            return 1;
        }
        return 0;
    }
    display_item_status_message(entity, item, action_type);
    {
        DungeonGlobalStatus *counter = &g_dungeon_status;
        (*(u16 *)&counter->unk_0A)--;
    }
    return 1;
}
