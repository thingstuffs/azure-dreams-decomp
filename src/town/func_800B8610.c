#include "common.h"

extern s8 *strcat(u8 *dst, const u8 *src);
extern void set_display_entry_text_and_position(s32 entry, const u8 *text, s32 text_style, s32 x, s32 y);
extern u8 *get_mode_specific_value(void *entry);

extern s32 D_800892C0[3];
extern u8 D_8008933C[];

/* Builds and displays an entry's formatted text. */
void draw_formatted_monster_status_text(void *entry, void *display) {
    u8 text[64];

    memcpy(text, D_800892C0, 5);
    strcat(text, (u8 *)entry + 0x34);
    strcat(text, D_8008933C);
    strcat(text, get_mode_specific_value(entry));
    set_display_entry_text_and_position(*(s32 *)((u8 *)display + 0x10), text, 0, 0x47, 0x88);
}
