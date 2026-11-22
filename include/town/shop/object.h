#ifndef TOWN_SHOP_OBJECT_H
#define TOWN_SHOP_OBJECT_H
/* Prototypes of the functions defined in src/town/shop/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/item_menu.h"
#include "shared/menu_display.h"
#include "shared/sprite_part_command.h"
#include "shared/object_node.h"

struct ActorRecord;
struct Copy4;
struct ItemMenuTransition;
struct AlternateStorageOwner;
struct S_800B1730_0;
struct S_800B2CE8_0;

/* Two words passed to the CD read command. */
typedef struct MonsterStatusCdDescriptor {
    s32 data_word;
    s32 sector;
} MonsterStatusCdDescriptor;

/* Allocated shop status body advanced through its first callback. */
typedef struct ShopFirstCallbackObject {
    /* 0x00 */ void (*first_callback)(struct ShopFirstCallbackObject *object);
    /* 0x04 */ struct ActorRecord *actor;
    /* 0x08 */ s16 slot_index; /* selects the display-entry setup path */
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 opening_step; /* monster-status opening sequence */
    /* 0x10 */ s32 palette_index;
    /* 0x14 */ SpritePartCommand *texture; /* third argument forwarded by the display-entry setup */
    /* 0x18 */ u8 pad_18[0x48];
    /* 0x60 */ MenuDisplayBlock display_template;
    /* 0x70 */ DisplayPositionWords display_position;
    /* 0x7C */ DisplayPositionWords resource_position;
    /* 0x88 */ ItemMenuPart display;
    /* 0x98 */ ItemMenuPart **parts;
    /* 0x9C */ u16 *allocations[6]; /* part table, two banks of two buffers and the null terminator */
    /* 0xB4 */ u8 pad_B4[0x1C];
    /* 0xD0 */ s32 read_handle;
    /* 0xD4 */ s32 completion_handle;
    /* 0xD8 */ MonsterStatusCdDescriptor read_descriptor;
    /* 0xE0 */ s32 transfer_data;
} ShopFirstCallbackObject;

/* create_monster_status_object.c */
void *create_monster_status_object(struct ActorRecord *actor, s32 slot_index, s32 x, s32 y, s32 z);

/* create_item_menu_handler_object.c */
ItemMenuObjectNode *create_item_menu_handler_object(ItemMenuStateNode *owner);

/* initialize_storage_menu_slots.c */
void initialize_storage_menu_slots(struct AlternateStorageOwner *object);

/* initialize_item_menu_object_slots.c */
void initialize_item_menu_object_slots(ItemMenuObject *object);

/* initialize_storage_menu_resources.c */
s32 func_800B4ED8(void *object, s32 resource_id);
s32 initialize_storage_menu_resources(void *object, s32 resource_id);

/* ease_paired_objects_to_presets.c */
struct ItemMenuInputObject;
void ease_paired_objects_to_presets(struct ItemMenuInputObject *pair_state);

/* invoke_item_menu_node_callback.c */
void invoke_item_menu_node_callback(struct ItemMenuTransition *state);

/* invoke_object_first_callback.c */
void invoke_object_first_callback(ShopFirstCallbackObject *obj);

/* link_item_menu_object_entries.c */
ItemMenuPart *link_item_menu_object_entries(ItemMenuPart **parts);

/* lshop_g00008.c */
void clear_shop_object_and_link(u8 *object_ref);
void release_lshop_entry(s32 slotIndex);
void compact_lshop_entry_list(void);
void *find_unused_item_slot(void **slot_list);
void append_town_item(const struct Copy4 *input);

/* apply_shop_object_slot_colors.c */
void apply_shop_object_slot_colors(ObjectNodeHeader *node);

/* set_advance_inner_value_callback.c */
void set_advance_inner_value_callback(ObjectNodeHeader *object);

/* set_apply_record_values_callback.c */
void set_apply_record_values_callback(ObjectNodeHeader *object);

/* set_shop_fade_out_callback.c */
void set_shop_fade_out_callback(ObjectNodeHeader *object);

/* set_shop_object_ready.c */
void set_shop_object_ready(struct S_800B1730_0 *object);

#endif
