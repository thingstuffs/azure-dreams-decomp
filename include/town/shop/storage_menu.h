#ifndef TOWN_SHOP_STORAGE_MENU_H
#define TOWN_SHOP_STORAGE_MENU_H

#include "common.h"
#include "shared/item_menu.h"
#include "shared/timed_stream.h"

/* Storage menu display parts; offsets follow complete recovered callbacks. */
typedef struct StorageEntryPosition {
    u8 pad_00[8];
    s16 x;
    s16 y;
    u8 pad_0C[2];
    s8 mode;
} StorageEntryPosition;
typedef struct StorageEntry {
    void *text;
    StorageEntryPosition *position;
} StorageEntry;
/* Display record load_storage_display_resource fills (allocate_object_and_mark_failed_setup_for_cleanup passes
 * the monster-status display body): the shared part vector, the part table and its buffer list. */
typedef struct StorageWork {
    u8 pad_00[0x7C];
    DisplayPositionWords vector;
    u8 pad_88[0x10];
    ItemMenuPart **parts; /* +0x98: part table from realloc_field_0_buffer */
    s32 buffer; /* +0x9C: first word of the buffer list realloc_field_0_buffer fills */
} StorageWork;
typedef struct StorageOwner {
    void *owner;
    u8 pad_04[8];
    s32 edge_flags; /* +0x0C: low two bits mark the control range bounds */
    u8 pad_10[4];
    FrameState cursor; /* +0x14: cursor stream initialize_storage_cursor starts on part 4 */
    u8 pad_20[0x38];
    ItemMenuPart *chain; /* +0x58: part chain installed by create_storage_owner_menu */
    ItemMenuPart **parts; /* +0x5C: the 41-part table initialize_object_resources builds (StorageMenuObject.parts) */
} StorageOwner;
typedef struct StorageSource {
    u8 pad_00[0x2C];
    u8 page[0x14];
    s32 value;
} StorageSource;
typedef struct StoragePageOwner {
    StorageSource *source;
    u8 pad_04[0x58];
    ItemMenuPart **parts; /* +0x5C: the storage owner's part table */
} StoragePageOwner;
typedef union StorageDisplayBlock {
    s32 words[4];
    ItemMenuDisplayBlock display;
} StorageDisplayBlock;
typedef union StorageVector {
    DisplayPositionWords words;
    struct { u8 pad_00[8]; s16 z; } position;
} StorageVector;
typedef struct StorageDisplayLinks {
    s32 unused;
    ItemMenuDisplayBlock *display;
    StorageVector *position;
} StorageDisplayLinks;
typedef struct StorageMenuObject {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x18];
    u8 *data;
    u8 pad_24[0x28];
    ItemMenuDisplayLinks links;
    ItemMenuPart *chain;
    ItemMenuPart **parts;
    u16 *allocations[8];
} StorageMenuObject;
typedef struct StorageMenuNode {
    ObjectNodeHeader header;
    StorageMenuObject menu;
} StorageMenuNode;

void arrange_storage_item_columns(StorageEntry **objects);
void refresh_storage_page(StoragePageOwner *object);
void *process_target_with_code_33(void *target);
void *process_target_with_code_41(void *parts);
StorageMenuNode *create_storage_item_menu(ItemMenuStateNode *owner);
StorageMenuNode *create_storage_owner_menu(ItemMenuStateNode *owner);
s32 load_storage_display_resource(StorageWork *work, s32 resource);

void forward_offset_to_effect_finalizer(void *node);

#endif
