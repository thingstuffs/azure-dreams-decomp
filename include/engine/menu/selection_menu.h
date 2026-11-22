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
struct ObjectNodeHeader;

/* Controller state shared by the input, fade and cleanup callbacks. */
typedef struct MenuSelectionBody {
    u8 pad_00[4];
    void *saved_callback;
    s32 fade_ticks;
    s32 repeat_ticks;
    s32 animation_frames;
    s32 animation_tick;
    s32 previous_selection;
    s32 selected_entry;
    s32 result;
    void *pending_callback;
    struct ObjectNodeHeader *attachment;
    u8 pad_2C[4];
    MenuDisplayBlock gauge_block;
    DisplayPositionWords gauge_vector;
    u8 pad_4C[0xC];
    MenuDisplayNode gauge; /* The factory installs this embedded display at node +0x0C. */
    MenuSelectionWidgets *widgets;
    u16 *buffers[12];
    u8 pad_9C[4];
    struct ObjectNodeHeader *owner;
    u8 highlight[6];
    u8 pad_AA[2];
} MenuSelectionBody;

void animate_six_entry_selection_cursor(MenuSelectionWidgets *widgets, MenuSelectionBody *anim);

#endif
