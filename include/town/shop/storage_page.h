#ifndef TOWN_SHOP_STORAGE_PAGE_H
#define TOWN_SHOP_STORAGE_PAGE_H

#include "shared/timed_stream.h"

struct ItemMenuPart;
struct DungeonItemEntry;

/* The icon, text and label builders all traverse ten entries starting at
 * current * 10, bounded by count. The two menu owners store this at
 * different offsets but pass the same fields to those builders. */
typedef struct StoragePage {
    int current;
    int last;
    unsigned char pad_08[4];
    int count;
} StoragePage;
typedef struct StorageSource {
    unsigned char pad_00[0x2C];
    StoragePage page;
    unsigned char pad_3C[4];
    struct DungeonItemEntry **entries;
} StorageSource;
typedef struct AlternateStorageSource {
    unsigned char pad_00[0x1C];
    StoragePage page;
    unsigned char pad_2C[0x10];
    struct DungeonItemEntry **entries;
} AlternateStorageSource;
typedef struct AlternateStorageOwner {
    AlternateStorageSource *source;
    unsigned char pad_04[0x10];
    unsigned int flags;
    unsigned char pad_18[4];
    FrameState cursor;
    unsigned char panel[0x48];
    unsigned char pad_70[0x38];
    struct ItemMenuPart **parts;
} AlternateStorageOwner;
void fill_ten_paged_entry_slots(struct ItemMenuPart **outputs, StoragePage *page_info,
                                struct DungeonItemEntry **entries_base);

#endif
