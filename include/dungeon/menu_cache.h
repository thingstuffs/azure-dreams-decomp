#ifndef DUNGEON_MENU_CACHE_H
#define DUNGEON_MENU_CACHE_H

#include "common.h"

#include "engine/node/registration.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/item_menu.h"
#include "shared/sprite_part_command.h"
#include "town/shop/object.h"

/* Only this player body uses both scratch pointers as indexed familiar links. */
static inline ActorRecord *read_cached_familiar_link(const u8 *actor_base)
{
    /* The link walk adds the constant offset of the first familiar field. */
    return *(void *const *)(actor_base + (unsigned long)&((ActorRecord *)0)->unk_AC.address);
}

static inline ActorRecord *get_cached_player_familiar(s32 slot)
{
    unsigned long scaled_slot = slot * sizeof(void *);
    const u8 *actor_base = (const u8 *)primary_actor_record;
    /* The indexed offset is the first operand of the address addition. */
    const u8 *slot_address = (const u8 *)(scaled_slot + (unsigned long)actor_base);

    return read_cached_familiar_link(slot_address);
}

s32 get_menu_actor_index(void *actor);
void *get_menu_actor(s32 index);
s32 get_menu_actor_mask(void);
s32 list_menu_actor_records(void **records, s32 include_primary);
s32 list_menu_actor_records_with_primary(void **records);
s32 list_menu_linked_actor_records(void **records);
s32 get_familiar_menu_state_mask(void);
s32 count_menu_familiars(void);

typedef struct MenuEntryObject {
    ObjectNodeHeader node;
    ShopFirstCallbackObject state;
} MenuEntryObject;

s32 prepare_menu_entries(ShopFirstCallbackObject *state, s32 count);
ItemMenuPart *link_menu_entries(ItemMenuPart **entries);
void initialize_menu_entry(ShopFirstCallbackObject *state, ActorRecord *actor, s32 slot_index, s32 x, s32 y, s32 z);
void invoke_menu_callback(ShopFirstCallbackObject *state);
int draw_tinted_node_sprites_scratch(void *forwarded_ptr, int unused_arg, void *second_ptr);
void release_null_terminated_entries(u16 **resources);
MenuEntryObject *allocate_menu_entry_object(ActorRecord *actor, s32 slot_index, s32 x, s32 y, s32 z);
void release_menu_entry_object(MenuEntryObject *object);
ObjectNodeHeader *allocate_menu_pair(ObjectNodeHeader *owner, s32 position, s32 mode);
ObjectNodeHeader *allocate_menu_pair_default(ObjectNodeHeader *owner, s32 position);


/* The list header's body is installed by the item display setup routine. */
typedef struct CachedItemList {
    ObjectNodeHeader *owner;
    ObjectNodeHeader *panels[2];
    DungeonItemEntry **entries;
    DungeonItemEntry *extra_entries[2];
    s32 position;
    s32 count;
    s32 page;
    s32 last_page;
    s32 excluded_count;
    s32 active_panel;
    s32 script_pending;
    s32 mode;
} CachedItemList;

typedef struct CachedItemListNode {
    ObjectNodeHeader header;
    CachedItemList list;
} CachedItemListNode;

/* A retry returns zero while waiting, one on success, or the allocated node address. */
typedef ObjectNodeHeader *CachedMenuRetryResult;

/* The body of the node that allocates the 40 display parts. */
typedef struct MenuPanelState {
    void *saved_update;
    CachedMenuRetryResult (*resume)(struct MenuPanelState *display);
    s32 step;
    s32 repeat_delay;
    s32 enabled;
    CachedItemListNode *owner;
    CachedItemList *list;
    s32 visible_count;
    s32 last_visible_page;
    FrameState cursor;
    u8 panel[0x48];
    ItemMenuDisplayBlock display;
    ItemMenuDisplayPosition display_position;
    DisplayPositionWords part_common;
    ItemMenuDisplayLinks links;
    ItemMenuPart *draw_chain;
    ItemMenuPart **parts;
    u16 *part_resources[1];
} MenuPanelState;


typedef struct CachedItemDisplayNode {
    ObjectNodeHeader header;
    MenuPanelState state;
} CachedItemDisplayNode;

void initialize_item_menu_panel_rectangle(void *record);
void layout_item_menu_upper_pair_columns(ItemMenuPart **parts);
void layout_item_menu_lower_item_columns(ItemMenuPart **parts);
void position_item_menu_side_indicators(ItemMenuPart **parts);
void layout_item_menu_lower_pair_columns(ItemMenuPart **parts);
CachedItemDisplayNode *create_item_display(ObjectNodeHeader *owner);
CachedItemDisplayNode *create_open_item_display(ObjectNodeHeader *owner);
void update_item_page_bounds(MenuPanelState *display);
extern u8 cached_item_secondary_cursor[];
CachedMenuRetryResult retry_item_pair_open(MenuPanelState *display);
CachedMenuRetryResult open_item_display_selection_action(MenuPanelState *display);
void advance_item_display_resume(MenuPanelState *display);
void confirm_item_selection(MenuPanelState *display);
void poll_item_display_input(MenuPanelState *display);
void cancel_item_selection(MenuPanelState *display);
void populate_item_page_text(MenuPanelState *display);
void populate_item_page_indicators(ItemMenuPart **parts, MenuPanelState *display);
void refresh_item_cursor_pair(MenuPanelState *display);
void initialize_item_parts(MenuPanelState *display);
/* The resident resource allocator appends the packet buffer to the same pointer pool. */

void populate_item_labels(ItemMenuPart **parts, MenuPanelState *display);
void position_item_cursors(MenuPanelState *display);
void populate_item_icons(MenuPanelState *display);
void refresh_item_page(MenuPanelState *display);
void redraw_item_selection(MenuPanelState *display);
void initialize_item_request(MenuPanelState *display, CachedItemListNode *owner);
void configure_item_display(MenuPanelState *display, CachedItemListNode *owner);
s32 prepare_item_parts(MenuPanelState *display, s32 count);
ItemMenuPart *link_item_display_entries(ItemMenuPart **entries);

void fade_color_to_gray(void *object, s32 unused);
void refresh_item_cursor_graphics(MenuPanelState *panel);
void resume_item_display(ObjectNodeHeader *node);
void update_menu_panel_colors(MenuPanelState *state);
void advance_menu_panel_scale(MenuPanelState *state);

extern const u8 menu_entry_link_table[];


#endif
