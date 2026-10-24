#include "shared/actor_property_flags.h"

struct ObjectNodeHeader;
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern u8 D_800E0F2D[];
extern u8 D_800E0F44[];
extern u8 D_800E0F65[];
extern u8 D_800E0F85[];

extern void apply_entity_effects(void *);
#include "dungeon/player/item.h"
extern void clear_slot_and_update_linked_state(s32);
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 clear_byte_and_advance(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void display_formatted_context_message(void *);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void place_actor_item(void *, s32);
extern void display_item_status_message(void *, s32, s16);
extern s32 feed_actor_restore_mp(void *, s32, s32);
extern void create_colored_effect_with_event(struct ObjectNodeHeader *source, s32 color, unsigned short event_id);

/* Applies an entity action, updates its state, and displays the result. */
s32 apply_item_and_update_matching_actor_state(void *entity, s32 action_id, s16 action_arg) {
    s16 match_state;
    s32 message_id;
    u16 type_flags;
    u8 update_count;

    match_state = 0;
    if (entity == ((u8 *)dungeon_actor_ring_anchor)) {
        *(s32 *)((u8 *)entity + 0x110) = action_id;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, action_id, action_arg);

        if (((u8 *)entity)[0x25] == ((u8 *)entity)[0x66]) {
            match_state = 1;
        }

        type_flags = entity_action_selectors[((u8 *)entity)[0x13]];
        if ((feed_actor_restore_mp(entity, ((u32)type_flags >> 8) & 3, action_id) << 16) == 0) {
            place_actor_item(entity, action_id);
            return 1;
        }

        if (match_state != 0) {
            update_count = ((u8 *)entity)[4];
            if (update_count < 0xFF) {
                ((u8 *)entity)[4] = update_count + 1;
                apply_entity_effects(entity);
            }
        }

        if ((*(u32 *)((u8 *)entity + 0x14) & ACTOR_PARTY_MEMBER) != 0) {
            if (match_state == 0) {
                if (((u8 *)entity)[0x25] != ((u8 *)entity)[0x66]) {
                    match_state = -1;
                }
            }

            message_id = get_unused_text_buffer();
            if (match_state < 0) {
                clear_byte_and_advance(expand_text_control_codes(D_800E0F2D,
                                            append_entity_display_text(entity, message_id)));
            } else if (match_state != 0) {
                clear_byte_and_advance(expand_text_control_codes(D_800E0F44,
                                            append_entity_display_text(entity, message_id)));
            } else {
                clear_byte_and_advance(expand_text_control_codes(D_800E0F65,
                                            append_entity_display_text(entity, message_id)));
            }
            display_text_with_fullwidth_adjustment(message_id);
        }

        create_colored_effect_with_event((u8 *)entity - 0x20, 0x20A0A0, 0x702);
        clear_slot_and_update_linked_state(action_id);
    } else {
        display_formatted_context_message(D_800E0F85);
        play_sound_if_enabled(0x506);
    }
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}

