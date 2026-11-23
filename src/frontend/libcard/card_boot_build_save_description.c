#include "frontend/card/save_image.h"
#include "shared/game_state.h"
#include "common.h"
#include "engine/town.h"
#include "frontend/libcard.h"
#include "main/data.h"
#include "sdk/libc.h"


/* Build text from a one-based index, global state, and a trailing value. */
void card_boot_build_save_description(CardSaveImage *save, s32 index) {
    u8 number_buffer[16];
    s32 *text_fragments;
    char *output_text_target;
    char *suffix_text_target;
    char *append_target;
    s32 saved_index;
    s32 selected_text;
    s32 trailing_value;

    saved_index = index;
    output_text_target = save->title_and_reserved;
    text_fragments = D_80028294;
    strcpy(output_text_target, text_fragments[0]);
    format_fullwidth_decimal(saved_index + 1, number_buffer);
    strcat(output_text_target, number_buffer);
    strcat(output_text_target, text_fragments[3]);
    strcat(output_text_target, 0x8001020C);
    strcat(output_text_target, text_fragments[3]);

    append_target = output_text_target;
    if (GAME_STATE->dungeon_save_marker != 0) {
        selected_text = text_fragments[1];
    } else {
        selected_text = text_fragments[2];
    }
    strcat(append_target, selected_text);

    suffix_text_target = save->title_and_reserved;
    strcat(suffix_text_target, D_800282A0);
    trailing_value = GAME_STATE->tower_entry_count;
    format_fullwidth_decimal(trailing_value, number_buffer);
    strcat(suffix_text_target, number_buffer);
}
