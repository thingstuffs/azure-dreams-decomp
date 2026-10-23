#include "common.h"

typedef struct ImageEntry {
    u8 pad0[8];
    s16 width;
    u8 padA[2];
} ImageEntry;

typedef struct SpriteFields {
    u32 pad0;
    u16 f4;
    u16 f6;
    u16 f8;
} SpriteFields;

typedef struct DisplayPair {
    u32 pad0;
    SpriteFields *src;
} DisplayPair;

typedef struct TownSlots {
    void **slots[8];
} TownSlots;

typedef struct TownObject {
    u8 pad0[0x13];
    u8 digit;
    u8 pad14[0x44];
    TownSlots *town;
} TownObject;

extern void draw_catalog_primary_detail(TownObject *);
extern u8 catalog_scroll_offset;
extern void *catalog_detail_pages[4];
extern u8 catalog_detail_fallback[16];
extern ImageEntry catalog_glyphs[];
extern DisplayPair *D_80129748;

/* Select the town object's digit graphic and adjust its display offset for width. */
void refresh_catalog_primary_detail(TownObject *obj)
{
    draw_catalog_primary_detail(obj);
    catalog_scroll_offset = 0;

    if (obj->digit == 0x31) {
        *obj->town->slots[7] = catalog_detail_fallback;
    } else {
        *obj->town->slots[7] = catalog_detail_pages[obj->digit / 16];
    }

    D_80129748->src->f8 = (5 - catalog_glyphs[obj->digit].width) * 6 + 0xD2;
}
