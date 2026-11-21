#ifndef FRONTEND_CARD_SERVER_MENU_H
#define FRONTEND_CARD_SERVER_MENU_H
/* Menu entry tables of the devkit card server's objects (the card UI's init_menu_entry_pointers fills the same
 * shape at +0x670 of its state). */
#include "frontend/libcard/display_node.h"

typedef struct CardDevMenuEntry {
    CardMenuDisplayNode display;
    s32 *settings;
    s32 unk_0C;
} CardDevMenuEntry;

typedef MenuDisplayBlock CardDevMenuPrimitive;

/* Devkit SME menu body with shared settings, the heading, and four rendered entries. */
typedef struct CardDevMenu4 {
    u8 unk_000[0xD4];
    s32 settings[3];
    CardDevMenuEntry heading;
    CardDevMenuEntry *entries[4];
    CardDevMenuEntry entry_blocks[4];
    CardDevMenuPrimitive primitives[4];
} CardDevMenu4;

void card_dev_init_sme_menu_entries(CardDevMenu4 *state, s32 entry_count);

/* Devkit slot window menu body with shared settings, the heading and its rendered entries. */
typedef struct CardDevMenu10 {
    u8 unk_000[0x1BC];
    s32 settings[3];
    CardDevMenuEntry heading;
    CardDevMenuEntry *entries[10];
    CardDevMenuEntry entry_blocks[10];
    CardDevMenuPrimitive primitives[10];
} CardDevMenu10;

void card_dev_init_slot_window_menu_entries(CardDevMenu10 *state, s32 entry_count);

/* Devkit options menu body with shared settings, the heading and its rendered entries. */
typedef struct CardDevMenu18 {
    u8 unk_000[0x19C];
    s32 settings[3];
    CardDevMenuEntry heading;
    CardDevMenuEntry *entries[18];
    CardDevMenuEntry entry_blocks[18];
    CardDevMenuPrimitive primitives[18];
} CardDevMenu18;

void card_dev_init_options_menu_entries(CardDevMenu18 *state, s32 entry_count);

struct CardDevRowEntry;

void card_dev_mark_row_entry_range(struct CardDevRowEntry *entries, s32 first, s32 count);

#endif
