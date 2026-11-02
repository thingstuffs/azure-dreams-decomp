#ifndef FRONTEND_CARD_SERVER_MENU_H
#define FRONTEND_CARD_SERVER_MENU_H
/* Menu entry tables of the devkit card server's objects (the card UI's init_menu_entry_pointers fills the same
 * shape at +0x670 of its state). */
#include "common.h"

typedef struct CardDevMenuEntry {
    s32 unk_00;
    s32 *primitive;
    s32 *settings;
    s32 unk_0C;
} CardDevMenuEntry;

typedef struct CardDevMenuPrimitive {
    s32 words[4];
} CardDevMenuPrimitive;

#endif
