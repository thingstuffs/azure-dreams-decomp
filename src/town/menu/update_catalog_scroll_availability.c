#include "town/menu/catalog.h"
struct Tbl {
    unsigned char unk0[4];
    unsigned char unk4;
    unsigned char unk5[3];
};


extern unsigned char catalog_scroll_offset[];
extern struct Tbl catalog_detail_images[];

/* Update entry flags from the global value and the entry's table threshold. */
void update_catalog_scroll_availability(CatalogDisplay *entry)
{
    unsigned char flags;

    if (catalog_scroll_offset[0] != 0) {
        entry->unk_0E |= 1;
    } else {
        entry->unk_0E &= 0xFE;
    }
    if (catalog_scroll_offset[0] < ((catalog_detail_images[entry->unk_13].unk4 - 3) << 4)) {
        flags = entry->unk_0E | 2;
    } else {
        flags = entry->unk_0E & 0xFD;
    }
    entry->unk_0E = flags;
}
