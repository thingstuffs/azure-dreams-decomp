#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

typedef struct DungeonObject {
    u8 pad_00[0x13];
    u8 unk_13;
    u32 flags_14;
    u8 pad_18[0xf8];
    s32 unk_110;
} DungeonObject;

extern u8 D_800E15BB[];
extern u8 D_800E15E5[];

#include "dungeon/player/item.h"
extern void clear_slot_and_update_linked_state(s32);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void *clear_byte_and_advance(s8 *byte_ptr);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern s32 set_or_clear_actor_status_slot(void *, s32, s32);
extern s32 display_text_with_fullwidth_adjustment(s8 *text);
extern s32 place_actor_item(void *, s32);
extern s32 display_item_status_message(void *, s32, s16);
extern s32 feed_actor_restore_mp(void *, s32, s32);

/* Processes an object action, dispatching the player case and reporting failure. */
s32 use_item_to_enrage_actor(DungeonObject *object, s32 action, s16 action_type) {
    void *message;
    void *message_end;

    if (object == ((DungeonObject *)dungeon_actor_ring_anchor)) {
        object->unk_110 = action;
        begin_deferred_item_action(object, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), object);
        return 0;
    }
    if ((u32) object <= 0x9FFFFFFFU) {
        display_item_status_message(object, action, action_type);
        if (feed_actor_restore_mp(object, (entity_action_selectors[object->unk_13] >> 6) & 3, 0) == 0) {
            place_actor_item(object, action);
            return 1;
        }
    }
    /*
     * BUG: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 when
     * insertion fails. This nonzero test suppresses feedback for success in slot 0 and gives
     * it for failure (-1). try_apply_confusion_status uses the correct nonnegative success
     * test.
     */
    if ((set_or_clear_actor_status_slot(object, STATUS_ANGER, 0x60) << 16) != 0) {
        if (object->flags_14 & ACTOR_PARTY_MEMBER) {
            message = get_unused_text_buffer();
            message_end = append_entity_display_text(object, message);
            message_end = expand_text_control_codes(D_800E15BB, message_end);
        } else {
            message = get_unused_text_buffer();
            message_end = message;
            message_end = expand_text_control_codes(D_800E15E5, message_end);
        }
        clear_byte_and_advance(message_end);
        display_text_with_fullwidth_adjustment(message);
    }
    clear_slot_and_update_linked_state(action);
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    return 1;
}
