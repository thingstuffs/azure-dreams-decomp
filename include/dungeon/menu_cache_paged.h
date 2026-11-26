#ifndef DUNGEON_MENU_CACHE_PAGED_H
#define DUNGEON_MENU_CACHE_PAGED_H

#include "town/shop/item_menu_cursor_transition_g00601.h"
#include "shared/object_node.h"
#include "dungeon/menu/state.h"

/* The paged menu allocates 26 draw parts and uses four groups of six rows. */
typedef struct CachedPagedMenu {
    void *motion_callback;
    s32 row_transition_duration;
    s32 row_transition_progress;
    s16 initial_x;
    s16 initial_y;
    s16 initial_depth;
    u8 pad_12[2];
    s16 distance_x;
    s16 distance_y;
    s16 distance_depth;
    u8 pad_1A[2];
    s32 selected_row;
    s32 previous_row;
    s32 opening_ticks;
    s32 entry_count;
    u8 pad_2C[8];
    s32 repeat_ticks;
    u8 pad_38[4];
    s32 owner_action;
    s32 source_mode;
    s32 item_index;
    s16 actor_index;
    s16 familiar_slot;
    u8 pad_4C[4];
    s32 owner_released;
    u8 entry_ids[8];
    u8 row_highlight[8];
    ObjectNodeHeader *owner;
    struct DungeonItemEntry *item;
    void *panel_packets;
    s32 position_words[4];
    s32 background_words[3];
    DisplayPositionWords part_vectors;
    ItemMenuDisplayLinks links;
    struct ItemMenuPart *draw_chain;
    ItemMenuRows *rows;
    u16 *resources[8];
} CachedPagedMenu;

/* The view's allocation and the other actions' success flags share this result.
 * The two dispatch consumers test it for zero. */
/* Null requests a retry. Completion returns the opened node or the sentinel. */
typedef ObjectNodeHeader *CachedPagedActionResult;
typedef CachedPagedActionResult (*CachedPagedMenuAction)(CachedPagedMenu *menu);
extern CachedPagedMenuAction cached_paged_menu_actions[19];

void release_paged_menu(CachedPagedMenu *menu);

void cancel_paged_menu(CachedPagedMenu *menu);
struct CachedStoragePanelPacket;
void initialize_cached_compact_panel_rectangle(struct CachedStoragePanelPacket *packet);
void initialize_paged_panel_packets(void *packets);
void initialize_paged_rows(CachedPagedMenu *menu);
void initialize_paged_request(CachedPagedMenu *menu, s32 item_index, s32 selected_row,
                                     ObjectNodeHeader *owner, struct DungeonItemEntry *item,
                                     s32 owner_action, s32 source_mode);
void setup_paged_menu(CachedPagedMenu *menu, s32 item_index, s32 selected_row,
                             ObjectNodeHeader *owner, s32 x, s32 y, struct DungeonItemEntry *item,
                             s32 owner_action, s32 source_mode);
s32 prepare_paged_parts(CachedPagedMenu *menu, s32 count);
ObjectNodeHeader *create_paged_menu_node(ObjectNodeHeader *owner, s32 item_index,
                                               s32 selected_row, s32 x, s32 y,
                                               struct DungeonItemEntry *item, s32 owner_action,
                                               s32 source_mode);
ObjectNodeHeader *open_paged_item_menu(ObjectNodeHeader *owner, s32 item_index,
                                             s32 selected_row, s32 x, s32 y,
                                             struct DungeonItemEntry *item);
ObjectNodeHeader *open_paged_action_item_menu(ObjectNodeHeader *owner, s32 item_index,
                                                    s32 selected_row, s32 x, s32 y,
                                                    struct DungeonItemEntry *item, s32 source_mode);
ObjectNodeHeader *open_paged_item_menu_with_source(ObjectNodeHeader *owner, s32 item_index,
                                                         s32 selected_row, s32 x, s32 y,
                                                         struct DungeonItemEntry *item, s32 source_mode);

CachedPagedActionResult dispatch_paged_menu_action(CachedPagedMenu *menu);
void run_paged_menu_action(CachedPagedMenu *menu);
void poll_paged_menu_input(CachedPagedMenu *menu);
void run_paged_menu_input(CachedPagedMenu *menu);
void update_cached_paged_row_motion(CachedPagedMenu *menu);
void advance_paged_menu_opening(CachedPagedMenu *menu, struct ObjectPosition *position,
                                       ItemMenuDisplayLinks *display);
void start_paged_menu_opening(CachedPagedMenu *menu, struct ObjectPosition *position,
                                     ItemMenuDisplayLinks *display);
void style_paged_rows(CachedPagedMenu *menu);

s32 menu_has_familiar(void);
void build_item_action_options(CachedPagedMenu *menu);

struct ActorRecord;
/* The item resolver returns the primary actor or a familiar record. */
void dispatch_paged_owner_resume(CachedPagedMenu *menu);
void close_paged_menu_owner(CachedPagedMenu *menu);
void resume_paged_menu_owner(CachedPagedMenu *menu);
ObjectNodeHeader *release_paged_menu_owner(CachedPagedMenu *menu);
CachedPagedActionResult confirm_paged_owner_close(CachedPagedMenu *menu);

CachedPagedActionResult view_paged_item(CachedPagedMenu *menu);
CachedPagedActionResult request_item_equip(CachedPagedMenu *menu);
CachedPagedActionResult request_item_unequip(CachedPagedMenu *menu);
CachedPagedActionResult request_item_use(CachedPagedMenu *menu);
CachedPagedActionResult request_item_hold(CachedPagedMenu *menu);
CachedPagedActionResult request_familiar_slot_change(CachedPagedMenu *menu);
CachedPagedActionResult request_familiar_alternate_deployment(CachedPagedMenu *menu);
CachedPagedActionResult open_paged_fusion_menu(CachedPagedMenu *menu);
CachedPagedActionResult open_paged_party_menu(CachedPagedMenu *menu);
CachedPagedActionResult open_paged_linked_actor_menu(CachedPagedMenu *menu);
CachedPagedActionResult request_target_item_use(CachedPagedMenu *menu);
CachedPagedActionResult request_familiar_deployment(CachedPagedMenu *menu);
CachedPagedActionResult request_item_registration_mode_two(CachedPagedMenu *menu);
CachedPagedActionResult request_item_registration_mode_one(CachedPagedMenu *menu);
CachedPagedActionResult request_marked_item_use(CachedPagedMenu *menu);
CachedPagedActionResult request_familiar_target(CachedPagedMenu *menu);
CachedPagedActionResult open_paged_familiar_prompt(CachedPagedMenu *menu);

extern const char *const cached_paged_item_action_labels[];
const char *get_paged_item_action_label(s32 action);


ObjectNodeHeader *open_paged_item_view(CachedPagedMenu *menu);

#endif
