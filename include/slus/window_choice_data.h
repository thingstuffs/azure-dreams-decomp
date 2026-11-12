#ifndef SLUS_WINDOW_CHOICE_DATA_H
#define SLUS_WINDOW_CHOICE_DATA_H

#include "common.h"
#include "engine/window/cursor_body.h"
#include "records/Rec_D_80081FDC.h"
#include "shared/object_node.h"

/* The three menu-choice constructors pass this record to cursor model setup. */
extern Rec_D_80081FDC menu_choice_display_data;

/* The node creator clears 0x49 words at 0x80082538. The next symbol is at
 * 0x80082660, leaving 0x128 bytes for this one resident node. Its body starts
 * after ObjectNodeHeader; the creator places position and sprite data in the
 * remaining space. The final word is outside its 0x124-byte clear. */
typedef struct MenuChoiceCursorStorage {
    ObjectNodeHeader node;
    WindowCursorBody body;
    u32 runtime_storage[0x28];
} MenuChoiceCursorStorage;

extern MenuChoiceCursorStorage menu_choice_cursor_storage;

#endif
