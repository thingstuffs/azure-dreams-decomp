#include "common.h"
#include "shared/game_state.h"
#include "engine/text.h"
#include "engine/util.h"
#include "sdk/libc.h"
#include "slus.h"

typedef struct {
    u8 pad0[8];
    u8 *data;
    u8 padC[0x44];
    void **handle;
} Func800B40ACArg;

extern u8 town_money_display_gold_suffix_message[];

/* Refreshes the display with the formatted global value and its suffix. */
void refresh_money_display(Func800B40ACArg *display) {
    u8 text[32];
    format_int_space_padded(GAME_STATE->town_money, 10, text);
    remap_flagged_string_bytes(text);
    strcat(text, town_money_display_gold_suffix_message);
    flag_optional_object_for_removal(*display->handle);
    *display->handle = build_positioned_text_glyphs(display->data + 0x48, text, 0);
}
