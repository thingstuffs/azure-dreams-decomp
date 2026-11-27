#include "common.h"
#include "shared/item_menu.h"
#include "town/menu/catalog.h"
#include "town/menu/catalog_glyph_data.h"
#include "town/menu.h"
#include "town/data.h"

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

#include "town/menu/catalog_scroll_data.h"
extern DisplayPair *D_80129748;

/* Select the town object's digit graphic and adjust its display offset for width. */
void refresh_catalog_primary_detail(CatalogDisplay *obj)
{
    draw_catalog_primary_detail(obj);
    catalog_scroll_offset = 0;

    if (obj->selected_entry == 0x31) {
        obj->parts.nodes[7]->handler = catalog_detail_fallback;
    } else {
        obj->parts.nodes[7]->handler = catalog_detail_pages[obj->selected_entry / 16];
    }

    D_80129748->src->f8 = (5 - catalog_glyphs[obj->selected_entry].detail_value) * 6 + 0xD2;
}
