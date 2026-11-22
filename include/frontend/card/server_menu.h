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

/* Four-entry SME panel created by the developer load screen. Its factory
 * clears 0x180 bytes and binds the four initialized entries at +0xF0. */
typedef struct CardDevMenu4 {
    struct CardDevLoadNode *owner;
    u8 first_payload[0x78];
    u8 label_payload[0x3C];
    MenuDisplayBlock frame_block;
    s32 frame_position[3];
    s32 settings[3];
    CardDevMenuEntry frame;
    CardDevMenuEntry *entries[4];
    CardDevMenuEntry entry_blocks[4];
    CardDevMenuPrimitive primitives[4];
} CardDevMenu4;

void card_dev_init_sme_menu_entries(CardDevMenu4 *state, s32 entry_count);

/* Each slot occupies 0x360 bytes including its 0x20-byte node header.
 * The factory clears this body and initializes its ten entries and blocks. */
typedef struct CardDevMenu10 {
    s32 slot_index;
    struct ObjectNodeHeader *owner;
    u8 title_text[0x48];
    u8 label_text[0x0C];
    u8 option_text[0x24];
    u8 value_text[0x30];
    u8 slot_packets[0x78];
    u8 option_packets[0x78];
    MenuDisplayBlock frame_block;
    s32 frame_position[3];
    s32 settings[3];
    CardDevMenuEntry frame;
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
