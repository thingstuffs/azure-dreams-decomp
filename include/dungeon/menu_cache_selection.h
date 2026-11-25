#ifndef DUNGEON_MENU_CACHE_SELECTION_H
#define DUNGEON_MENU_CACHE_SELECTION_H

#include "shared/item_menu.h"
#include "shared/menu_display.h"
#include "shared/object_node.h"
#include "town/shop/storage_menu.h"

typedef struct CachedSelectionPanel {
    u8 pad_00[4];
    ObjectNodeHeader *owner;
    void *row_packets;
    s32 duration;
    s32 progress;
    s32 selected_row;
    s32 previous_row;
    s32 repeat_delay;
    u8 pad_20[4];
    s32 enabled;
    u8 row_highlight[2];
    u8 pad_2a[2];
    StorageDisplayBlock display;
    ItemMenuDisplayPosition position;
    DisplayPositionWords part_vector;
    ItemMenuDisplayLinks links;
    ItemMenuPart *chain;
    ItemMenuPart **parts;
    u16 *resources[1];
} CachedSelectionPanel;

typedef struct CachedSelectionPanelNode {
    ObjectNodeHeader header;
    CachedSelectionPanel panel;
} CachedSelectionPanelNode;

extern u8 cached_selection_row_left_template[];
extern u8 cached_selection_row_middle_template[];
extern u8 menu_leaf_template_6[12];
extern char *cached_selection_row_indicator_texts[2];

void enqueue_script_message_command(void);
void call_message_mode_handler(void);
void complete_cached_message_transition(void *body);
void queue_menu_message(ObjectNodeHeader *node);
void poll_menu_owner_cancel(void *body);
void schedule_party_menu_close(ObjectNodeHeader *node);
void start_menu_message_mode(ObjectNodeHeader *node);
void schedule_menu_preview(ObjectNodeHeader *node);
void animate_selection_rows(CachedSelectionPanel *panel);
void process_selection_input(CachedSelectionPanel *panel);
void update_selection_panel(CachedSelectionPanel *panel);
void open_selection_panel(CachedSelectionPanel *panel);
void slide_selection_panel_out(CachedSelectionPanel *panel);
void initialize_selection_positions(CachedSelectionPanel *panel);
void initialize_selection_panel_packets(void *packets);
void populate_selection_parts(CachedSelectionPanel *panel);
void style_selection_rows(CachedSelectionPanel *panel);
void initialize_selection_display(CachedSelectionPanel *panel, ItemMenuDisplayLinks *links,
                                         StorageDisplayBlock *display, ItemMenuDisplayPosition *position);
void prepare_selection_rows(CachedSelectionPanel *panel, ObjectNodeHeader *owner);
void configure_selection_panel(CachedSelectionPanel *panel, ObjectNodeHeader *owner);
void release_selection_indicators(CachedSelectionPanel *panel);
void release_selection_panel(CachedSelectionPanelNode *node);
void enable_selection_panel(CachedSelectionPanelNode *node);
void schedule_selection_panel_open(ObjectNodeHeader *node);

s32 prepare_selection_parts(CachedSelectionPanel *panel, s32 count);

ItemMenuPart *link_selection_panel_entries(ItemMenuPart **parts);

#endif
