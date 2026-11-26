#ifndef DUNGEON_MENU_CACHE_CLOSE_H
#define DUNGEON_MENU_CACHE_CLOSE_H

#include "dungeon/menu_cache.h"
#include "engine/effect.h"
#include "shared/sprite_part_command.h"
#include "town/shop/storage_menu.h"

/* Shared leading owner link in the linked-actor and familiar prompt bodies. */
typedef struct CachedMenuOwnerLink {
    u8 pad_00[4];
    ObjectNodeHeader *owner;
} CachedMenuOwnerLink;

/* The fusion constructor owns the two display nodes and the result node. */
typedef struct CachedFusionMenu {
    /* The actor preview ends where a live actor keeps its action handler (0x8C bytes, pointer fields included). */
    u8 actor_preview[0x8C];
    ObjectNodeHeader *owner;
    ObjectNodeHeader *actor_choice;
    MenuEntryObject *confirmation_panel;
    ObjectNodeHeader *result_node;
} CachedFusionMenu;

typedef struct CachedItemActionMenu {
    ObjectNodeHeader *owner;
    u8 pad_04[4];
    DungeonItemEntry *selected_item;
    DungeonItemEntry *held_item;
    s32 selected_slot;
} CachedItemActionMenu;


void release_fusion_children(CachedFusionMenu *menu);
void *ensure_fusion_close(CachedFusionMenu *menu);
void start_fusion_close(CachedFusionMenu *menu);
void finish_fusion_cleanup(CachedFusionMenu *menu);

void queue_action_cleanup_message(CachedItemActionMenu *menu);
ObjectNodeHeader *release_action_node(ObjectNodeHeader *node);
void *ensure_action_close(CachedItemActionMenu *menu);
void start_action_close(CachedItemActionMenu *menu);
void finish_action_cleanup(ObjectNodeHeader *node);
ObjectNodeHeader *release_menu_pair_node(ObjectNodeHeader *node);
void *ensure_menu_pair_close(CachedItemList *list);
void start_menu_pair_close(CachedItemList *list);
void finish_menu_pair_cleanup(ObjectNodeHeader *node);
void poll_action_notice_cancel(void *body);
void poll_cached_action_owner_cancel(void *body);
void check_action_close_signal(void *body);
void schedule_action_menu_close(ObjectNodeHeader *node);

extern u8 item_action_nothing_found_notice[];
void show_cached_action_unavailable(void);
void poll_item_action_confirmation(CachedItemActionMenu *menu);
void initialize_item_action(CachedItemActionMenu *menu, ObjectNodeHeader *owner);
ObjectNodeHeader *create_item_action_dialog(ObjectNodeHeader *owner, s32 item_index);
ObjectNodeHeader *open_cached_inventory_or_dialog(ObjectNodeHeader *owner, s32 index);
void poll_item_action_notice(CachedItemActionMenu *menu);
ObjectNodeHeader *create_cached_elevator_notice(void);

/* The rectangle builder writes a pair of primitives and a closing command. */
typedef struct CachedStoragePanelPacket {
    u8 commands[0x3c];
    u8 closing_flags;
    u8 closing_command[0x0b];
} CachedStoragePanelPacket;

typedef struct CachedStoragePanel {
    FrameState cursor;
    s32 extra_entry_count;
    s32 regular_entry_count;
    s32 repeat_ticks;
    s32 enabled;
    s32 selected_extra_index;
    CachedStoragePanelPacket packet;
    DungeonItemEntry *extra_entries[2];
    StorageDisplayBlock display;
    ItemMenuDisplayPosition position;
    DisplayPositionWords part_common;
    ItemMenuDisplayLinks links;
    ItemMenuPart *draw_chain;
    ItemMenuPart **parts;
    u16 *resources[8];
    ObjectNodeHeader *owner;
    CachedItemList *list;
    void *saved_update;
    CachedMenuRetryResult (*resume)(struct CachedStoragePanel *panel);
} CachedStoragePanel;

void initialize_storage_parts(CachedStoragePanel *panel);
void handle_storage_panel_input(CachedStoragePanel *panel);
void poll_storage_panel_input(CachedStoragePanel *panel);
void confirm_storage_selection(CachedStoragePanel *panel);
void cancel_storage_selection(CachedStoragePanel *panel);
void locate_storage_cursor(CachedStoragePanel *panel);
struct RECT;
void initialize_storage_rectangle(CachedStoragePanelPacket *packet, s32 height_index);

ItemMenuPart *link_storage_display_entries(ItemMenuPart **entries);
void configure_storage_display_blocks(ItemMenuDisplayLinks *state, StorageDisplayBlock *primary,
                                             ItemMenuDisplayPosition *secondary);
void initialize_storage_request(CachedStoragePanel *panel, ObjectNodeHeader *owner);
void configure_storage_panel(CachedStoragePanel *panel, ObjectNodeHeader *owner);
s32 prepare_storage_parts(CachedStoragePanel *panel, s32 count);

void release_storage_components(CachedStoragePanel *panel);
ObjectNodeHeader *release_item_display(ObjectNodeHeader *node);
ObjectNodeHeader *release_storage_display(ObjectNodeHeader *node);
void release_menu_pair_active_panel(ObjectNodeHeader *node);
void release_menu_pair_and_queue_message(void *body);

void schedule_menu_pair_close(ObjectNodeHeader *node);
extern SpritePartCommand cached_fixed_storage_cursor[];
extern SpritePartCommand cached_storage_one_row_frame[];
extern SpritePartCommand cached_storage_two_row_frame[];

void refresh_storage_header(CachedStoragePanel *panel);
void populate_storage_panel_rows(CachedStoragePanel *panel);
void refresh_storage_panel(CachedStoragePanel *panel);
void resume_storage_display(ObjectNodeHeader *node);
void resume_menu_pair_panel(ObjectNodeHeader *node);
void resume_menu_pair_for_familiar(ObjectNodeHeader *node);
s32 is_familiar_item(const DungeonItemEntry *item);
extern u8 cached_familiar_action_context[];

void initialize_menu_pair(CachedItemList *list, s32 position,
                                 ObjectNodeHeader *owner, s32 mode);
s32 create_cached_pair_panel(CachedItemList *list);
s32 reopen_cached_pair_panel(CachedItemList *list);
s32 reopen_menu_pair(ObjectNodeHeader *node);
ObjectNodeHeader *create_storage_display_node(ObjectNodeHeader *owner);
CachedMenuRetryResult try_storage_panel_reopen(CachedStoragePanel *panel);
CachedMenuRetryResult open_storage_selection_action(CachedStoragePanel *panel);
void advance_storage_panel_resume(CachedStoragePanel *panel);
void reopen_display_from_storage_panel(CachedStoragePanel *panel);

#endif
