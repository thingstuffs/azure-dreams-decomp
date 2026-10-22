#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"

typedef struct DungeonState {
    u8 pad0[0xA];
    u16 counter;
} DungeonState;

extern DungeonState D_80083460;
extern u8 dungeon_event_pending_flag[];
extern u8 D_800E0458[];
extern u8 D_800E0C78[];

extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 copy_four_text_bytes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern s32 write_text_byte_and_advance(s8 value, s8 *dest);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void display_text_with_fullwidth_adjustment(s8 *text);

/* Conditionally advances the dungeon counter and processes the input through the result chain. */
void announce_familiar_defeat(void *input_data) {
    void *context;
    u16 *flag_page;
    void *saved_input;
    s32 initial_result;
    s32 result;
    u16 counter;

    flag_page = (u16 *)0x80010000;
    saved_input = input_data;
    if (!(flag_page[0x3714 / 2] & 1)) {
        context = dungeon_event_pending_flag;
        {
            DungeonState *counter_state = &D_80083460;
            counter = counter_state->counter;
            ((u8 *)context)[0] = 1;
            counter_state->counter = counter + 1;
        }
    }
    initial_result = get_unused_text_buffer();
    result = expand_text_control_codes(D_800E0C78, append_entity_display_text(saved_input, initial_result));
    if (!(flag_page[0x3714 / 2] & 1)) {
        result = copy_four_text_bytes(D_800E0458,
            write_text_byte_and_advance(0x4C, write_text_byte_and_advance(0x11, result)));
    }
    clear_byte_and_advance(result);
    display_text_with_fullwidth_adjustment(initial_result);
}

