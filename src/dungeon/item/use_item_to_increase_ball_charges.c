#include "shared/entity_action_selectors.h"
#include "shared/item_ids.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern u8 D_800E14D8[];
extern u8 D_800E14EB[];
extern u8 D_800E1514[];

#include "dungeon/player/item.h"
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern u8 * copy_selected_text_without_terminator(void *, u8 *);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void place_actor_item(void *, s32);
extern void display_actor_item_status_message(void *, s32, s16);
extern s32 feed_actor_restore_mp(void *, s32, s32);


typedef struct S_800C1B1C_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800C1B1C_1;   /* base in use_item_to_increase_ball_charges */

typedef struct S_800C1B1C_2 {
    u8 pad_00[0x1];
    u8 unk_01;
    union { s8 s; u8 u; } unk_02;   /* accessed as both */
} S_800C1B1C_2;   /* ((S_800C1B1C_1 *)base)->unk_04 in use_item_to_increase_ball_charges */

/* Apply a target action or update the current item and display its result message. */
s32 use_item_to_increase_ball_charges(EntityRec *target, s32 action, s16 action_type, s32 action_arg)
{
    s32 *item_state;
    void *message;
    void *message_end;

    if (action_type == 13) {
        return process_record_and_update_linked_state(action, action_arg);
    }

    if (target == ((u8 *)dungeon_actor_ring_anchor)) {
        target->unk_110 = action;
        begin_mode_selected_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, action, action_type);
        if (feed_actor_restore_mp(
                target, entity_action_selectors[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3, 0) == 0) {
            place_actor_item(target, action);
            return 1;
        }
    } else {
        message = get_unused_text_buffer();
        item_state = ((s32 *)(&reference_tile_object.selected_item));
        if (((S_800C1B1C_2 *)(((S_800C1B1C_1 *)item_state)->unk_04))->unk_01 == ITEM_KIND_BALL) {
            message_end = expand_text_control_codes(
                D_800E14EB,
                copy_selected_text_without_terminator(
                    ((S_800C1B1C_1 *)item_state)->unk_04,
                    expand_text_control_codes(D_800E14D8, message)));
            play_sound_if_enabled(0x80F);
            if (((S_800C1B1C_2 *)(((S_800C1B1C_1 *)item_state)->unk_04))->unk_02.s < 99) {
                ((S_800C1B1C_2 *)(((S_800C1B1C_1 *)item_state)->unk_04))->unk_02.u++;
            }
        } else {
            message_end = expand_text_control_codes(D_800E1514, message);
        }
        clear_byte_and_advance(message_end);
        display_text_with_fullwidth_adjustment(message);
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(action);
    return 1;
}
