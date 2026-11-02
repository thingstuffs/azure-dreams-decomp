#ifndef TOWN_MENU_CATALOG_PARTS_H
#define TOWN_MENU_CATALOG_PARTS_H

#include "shared/item_menu.h"

typedef struct CatalogFrameEntry {
    void *value;
    u16 x;
    u16 y;
} CatalogFrameEntry;

/* Templates write three full words. Layout and transition handlers also
 * access these measured halfwords, including both signs at +6 and +8. */
typedef union CatalogDisplayVector {
    DisplayPositionWords words;
    struct {
        u8 pad_00[2];
        u16 unk_02;
        u8 pad_04[2];
        u16 unk_06;
        u16 unk_08;
        u8 pad_0A[2];
    } unsigned_halves;
    struct {
        u8 pad_00[6];
        s16 unk_06;
        s16 unk_08;
        u8 pad_0A[2];
    } signed_halves;
} CatalogDisplayVector;

/* The catalog cursor position reads the two halfwords that the shared part
 * position view leaves unnamed, and reads x/y as unsigned screen coordinates. */
typedef struct CatalogCursorPosition {
    u32 color;
    u16 scale_x;
    u16 scale_y;
    u16 x;
    u16 y;
} CatalogCursorPosition;

typedef struct CatalogCursorPart {
    void *handler;
    CatalogCursorPosition *position;
} CatalogCursorPart;

/* Slots 0..96 are display parts; slot 97 carries the selection cursor. */
typedef struct CatalogNodeSlots {
    ItemMenuPart *entries[97];
    CatalogCursorPart *cursor;
} CatalogNodeSlots;

extern ItemMenuPart *catalog_display_node_slots[98];
extern CatalogFrameEntry catalog_frame_layout[14];

#endif
