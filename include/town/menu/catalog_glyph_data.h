#ifndef TOWN_MENU_CATALOG_GLYPH_DATA_H
#define TOWN_MENU_CATALOG_GLYPH_DATA_H

#include "common.h"

/* Twelve-byte catalog entry: the two halfwords serve different display paths. */
typedef struct CatalogGlyphEntry {
    void *image;
    void **image_ref;
    s16 detail_value; /* s16 by opposite-sign trial: both readers (refresh_catalog_primary_detail,
                       * refresh_catalog_secondary_detail) load lh; as u16 each would need an (s16) cast */
    u16 label_width;
} CatalogGlyphEntry;

extern CatalogGlyphEntry catalog_glyphs[];

#endif
