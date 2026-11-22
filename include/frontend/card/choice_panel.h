#ifndef FRONTEND_CARD_CHOICE_PANEL_H
#define FRONTEND_CARD_CHOICE_PANEL_H
#include "frontend/libcard/display_node.h"
#include "shared/timed_stream.h"
/* Common pointer-table prefix read by the two-row CARD_DEV initializer. */
typedef struct CardDevChoicePanelPrefix {
    u8 pad_00[0x60];
    CardMenuDisplayNode **children;
} CardDevChoicePanelPrefix;

typedef struct CardDevPairedChoiceData {
    s32 values[2];
    FrameNode *entries[2];
} CardDevPairedChoiceData;

extern CardDevPairedChoiceData card_dev_paired_choice_data;
extern FrameNode card_dev_choice_cursor_data;

/* The developer slot constructor binds four entries to the table at +0x60.
 * The pointer table is external to the 0xE4-byte body. */
typedef struct CardDevSlotEntry {
    CardMenuDisplayNode display;
    s32 *settings;
    s32 unk_0C;
} CardDevSlotEntry;

typedef struct CardDevSlotMenu {
    struct ObjectNodeHeader *owner;
    FrameState cursors[2];
    u8 pad_1C[8];
    s32 selection;
    MenuDisplayBlock frame_block;
    s32 frame_position[3];
    s32 settings[3];
    CardDevSlotEntry frame;
    CardDevSlotEntry **entry_table;
    CardDevSlotEntry entries[4];
    MenuDisplayBlock primitives[4];
} CardDevSlotMenu;

void card_dev_init_slot_entry_tables(CardDevSlotMenu *menu, s32 entry_count);
#endif
