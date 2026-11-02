#include "common.h"
#include "shared/item_menu.h"
#include "town/menu/catalog.h"
#include "town/menu.h"
#include "town/data.h"

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

extern u8 catalog_scroll_offset;
extern ImageEntry catalog_glyphs[];
extern DisplayPair *D_80129748;

/* Select the town object's digit graphic and adjust its display offset for width. */
void refresh_catalog_primary_detail(CatalogDisplay *obj)
{
    draw_catalog_primary_detail(obj);
    catalog_scroll_offset = 0;

    if (obj->unk_13 == 0x31) {
        obj->parts.nodes[7]->handler = catalog_detail_fallback;
    } else {
        obj->parts.nodes[7]->handler = catalog_detail_pages[obj->unk_13 / 16];
    }

    D_80129748->src->f8 = (5 - catalog_glyphs[obj->unk_13].width) * 6 + 0xD2;
}
