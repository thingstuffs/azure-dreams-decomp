#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "dungeon/item/message.h"
#include "dungeon/system.h"
#include "dungeon/data.h"

extern s8 dungeon_event_pending_flag[];
extern u8 D_800E0C78[];

/* Conditionally advances the dungeon counter and processes the input through the result chain. */
void announce_familiar_defeat(void *input_data) {
    void *context;
    u16 *flag_page;
    void *saved_input;
    void *initial_result;
    void *result;
    u16 counter;

    flag_page = (u16 *)0x80010000;
    saved_input = input_data;
    if (!(flag_page[0x3714 / 2] & 1)) {
        context = dungeon_event_pending_flag;
        {
            DungeonGlobalStatus *counter_state = &g_dungeon_status;
            counter = counter_state->activity_counts.parts.pending_action_count;
            ((u8 *)context)[0] = 1;
            counter_state->activity_counts.parts.pending_action_count = counter + 1;
        }
    }
    initial_result = get_unused_text_buffer();
    result = expand_text_control_codes(D_800E0C78, append_entity_display_text(saved_input, initial_result));
    if (!(flag_page[0x3714 / 2] & 1)) {
        result = copy_four_text_bytes(familiar_defeat_text,
            write_text_byte_and_advance(0x4C, write_text_byte_and_advance(0x11, result)));
    }
    clear_byte_and_advance(result);
    display_text_with_fullwidth_adjustment(initial_result);
}

