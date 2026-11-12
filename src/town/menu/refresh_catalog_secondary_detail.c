#include "common.h"
#include "shared/item_menu.h"
#include "town/menu/catalog.h"
#include "town/menu.h"
#include "town/data.h"

typedef struct {
    void *image;
    void **image_ref;
    s16 value;
    u16 unused;
} ImageEntry;

typedef struct {
    u32 pad0;
    u16 f4;
    u16 f6;
    s16 f8;
    u16 fA;
} SpriteFields;

typedef struct {
    u32 pad0;
    SpriteFields *src;
} DisplayPair;

#include "town/menu/catalog_scroll_data.h"
extern u8 D_80126A0D[16];
extern ImageEntry catalog_glyphs[];
extern DisplayPair *D_80129780[3];

/* Select the town object's image and update its sprite field from the image entry. */
void refresh_catalog_secondary_detail(CatalogDisplay *town_obj)
{
    draw_catalog_secondary_detail(town_obj);
    D_80126A0D[0] = catalog_scroll_offset;

    if (town_obj->unk_14 == 0x31) {
        town_obj->parts.nodes[21]->handler = catalog_detail_fallback;
    } else {
        u32 t = town_obj->unk_14;
        town_obj->parts.nodes[21]->handler = catalog_detail_pages[t >> 4];
    }

    D_80129780[0]->src->f8 =
        (s16)(((5 - catalog_glyphs[town_obj->unk_14].value) * 6) + 0xD2);
}
