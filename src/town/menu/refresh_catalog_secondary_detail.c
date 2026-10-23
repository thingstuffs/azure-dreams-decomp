#include "common.h"

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

typedef struct {
    void **slots[22];
} TownSlots;

typedef struct {
    u8 pad0[0x14];
    u8 index;
    u8 pad15[0x43];
    TownSlots *town;
} TownObject;

extern void draw_catalog_secondary_detail(TownObject *);

extern u8 catalog_scroll_offset[16];
extern u8 D_80126A0D[16];
extern void *catalog_detail_pages[4];
extern ImageEntry catalog_glyphs[];
extern u8 catalog_detail_fallback[16];
extern DisplayPair *D_80129780[3];

/* Select the town object's image and update its sprite field from the image entry. */
void refresh_catalog_secondary_detail(TownObject *town_obj)
{
    draw_catalog_secondary_detail(town_obj);
    D_80126A0D[0] = catalog_scroll_offset[0];

    if (town_obj->index == 0x31) {
        *town_obj->town->slots[21] = catalog_detail_fallback;
    } else {
        u32 t = town_obj->index;
        *town_obj->town->slots[21] = catalog_detail_pages[t >> 4];
    }

    D_80129780[0]->src->f8 =
        (s16)(((5 - catalog_glyphs[town_obj->index].value) * 6) + 0xD2);
}
