#include "common.h"
#include "shared/game_state.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "dungeon/item/message.h"
#include "dungeon/system.h"
#include "dungeon/data.h"

extern u8 familiar_defeated_message[];

/* Conditionally advances the dungeon counter and processes the input through the result chain. */
void announce_familiar_defeat(void *input_data) {
    signed char *event_flag;
    void *saved_input;
    void *initial_result;
    void *result;
    u16 counter;

    saved_input = input_data;
    if (!(GAME_STATE->log.head.flags & 1)) {
        event_flag = &dungeon_event_pending_flag;
        {
            DungeonGlobalStatus *counter_state = &g_dungeon_status;
            counter = counter_state->activity_counts.parts.pending_action_count;
            *event_flag = 1;
            counter_state->activity_counts.parts.pending_action_count = counter + 1;
        }
    }
    initial_result = get_unused_text_buffer();
    result = expand_text_control_codes(familiar_defeated_message, append_entity_display_text(saved_input, initial_result));
    if (!(GAME_STATE->log.head.flags & 1)) {
        result = copy_four_text_bytes(familiar_defeat_text,
            write_text_byte_and_advance(0x4C, write_text_byte_and_advance(0x11, result)));
    }
    clear_byte_and_advance(result);
    display_text_with_fullwidth_adjustment(initial_result);
}

