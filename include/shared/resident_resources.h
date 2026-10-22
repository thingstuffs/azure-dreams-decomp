#ifndef SHARED_RESIDENT_RESOURCES_H
#define SHARED_RESIDENT_RESOURCES_H
#include "common.h"


/* Exact access views shared across registered binary consumers. */
/* Signed key and bitmap-bit value in the resident zero-terminated mapping table. */
/* Borrowed key-to-bitmap mapping table rooted at resident_bitmap_key_map.
 * set_resident_bits_for_matching_key follows entries until the zero-key terminator. */
typedef struct ResidentBitmapEntry {
    short key; /* lookup key matched against the request; zero terminates the table */
    short value; /* bitmap bit identifier passed to set_resident_bitmap_bit for a matching key */
} ResidentBitmapEntry;

/* Category/index pair in the twenty-entry table shared by resource slot operations. */
/* One of twenty resident item-data slot keys; alloc_item_data_slot fills a free pair.
 * The category/index pair selects the item record that receives the associated 19-byte data block. */
typedef struct ResourceCategoryPair {
    short a; /* item category index; the pair (0,0) identifies a free slot */
    short b; /* record index within the item category */
} ResourceCategoryPair;

/* Signed cached object code and state selector in D_80083D78. */
typedef struct CachedObjectCodePair {
    short unk_00;
    short unk_02;
} CachedObjectCodePair;

/* Signed halfword at +A used to initialize a resource-slot state. */
typedef struct ResourceSlotStateView {
    unsigned char pad_00[0xA];
    short unk_0A;
} ResourceSlotStateView;

/* Twelve-byte resource-read state with one active word and two opaque signed words. */
typedef struct ResourceReadState {
    int field0;
    int pad4;
    int pad8;
} ResourceReadState;

#endif
