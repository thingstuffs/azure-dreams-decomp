#ifndef TOWN_SHOP_H
#define TOWN_SHOP_H

#include "common.h"
#include "shared/item_menu.h"


/* get_player_homerank.c */
s32 get_player_homerank(void);

struct S_800AE56C_0;
void dispatch_item_menu_entry_callback(struct S_800AE56C_0 *state, s32 callback_arg);
void invoke_item_menu_offset_handler(u8 *object, s32 callback_arg);

void initialize_item_menu_request_state(void *state, s32 base_value);


s32 count_town_items(void);
void fill_ten_paged_output_slots(s32 **outputs, s32 *page_info, s32 record_table);

struct ItemMenuPart;
struct ItemMenuObject;
void item_menu_no_op(struct ItemMenuPart **parts, struct ItemMenuObject *object);

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
typedef struct StorageWork {
    u8 pad_00[0x10];
    void *cursor;
    void **target;
    u8 pad_18[0x28];
    u8 page[0x28];
    u8 page_loader[0x14];
    DisplayPositionWords vector;
    u8 pad_88[0x10];
    s32 handle;
    s32 buffer;
} StorageWork;
typedef struct StorageOwner {
    void *owner;
    u8 pad_04[0x10];
    u8 cursor[0x3C];
    u8 pad_50[0xC];
    StorageWork *work;
} StorageOwner;
typedef struct StorageSource {
    u8 pad_00[0x2C];
    u8 page[0x14];
    s32 value;
} StorageSource;
typedef struct StoragePageOwner {
    StorageSource *source;
    u8 pad_04[0x58];
    StorageWork *work;
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
    u8 pad_00[0x4C];
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
void set_storage_entry_text(StorageEntry *entry, s32 text, s32 style, s16 x, s32 y);
void initialize_storage_cursor(StorageOwner *object);
void refresh_storage_page(StoragePageOwner *object);
void update_storage_display(StorageOwner *object);
void initialize_storage_display_links(StorageDisplayLinks *state, StorageDisplayBlock *primary, StorageVector *secondary);
StorageMenuNode *create_storage_item_menu(ItemMenuStateNode *owner);
StorageMenuNode *create_storage_owner_menu(ItemMenuStateNode *owner);
s32 load_storage_display_resource(StorageWork *work, s32 resource);

#endif
