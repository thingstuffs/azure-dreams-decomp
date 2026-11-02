#ifndef ENGINE_MENU_SELECTION_MENU_H
#define ENGINE_MENU_SELECTION_MENU_H
#include "common.h"
#include "shared/menu_display.h"

/* Widget links consumed by the six-entry selection animation. */
typedef struct MenuSelectionWidgets {
    u8 pad_00[4];
    MenuDisplayNode *entries[6];
    u8 pad_1C[4];
    MenuDisplayNode *cursor;
    MenuDisplayNode *secondary_cursor;
    MenuDisplayNode *secondary_entries[6];
} MenuSelectionWidgets;
/* Observed selection-controller fields, including the per-entry highlight
 * bytes. The saved callback remains a raw word until its signature is known. */
typedef struct MenuSelectionBody {
    u8 pad_00[4];
    s32 saved_callback_word;
    u8 pad_08[4];
    s32 repeat_ticks;
    s32 animation_frames;
    s32 animation_tick;
    s32 previous_selection;
    s32 selected_entry;
    s32 result;
    u8 pad_24[4];
    void *unk_28;
    u8 pad_2C[0x3C];
    MenuSelectionWidgets *widgets;
    u8 pad_6C[0x38];
    u8 highlight[6];
    u8 pad_AA[2];
} MenuSelectionBody;

void animate_six_entry_selection_cursor(MenuSelectionWidgets *widgets, MenuSelectionBody *anim);

#endif
