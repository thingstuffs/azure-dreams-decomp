#ifndef DUNGEON_MENU_CACHE_H
#define DUNGEON_MENU_CACHE_H

#include "common.h"

#include "shared/entity.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

/* This bank reads the player tail as well as the ActorRecord prefix. */
extern PlayerRecord *primary_actor_record;

s32 get_menu_actor_index(void *actor);
void *get_menu_actor(s32 index);
s32 get_menu_actor_mask(void);
s32 list_menu_actor_records(void **records, s32 include_primary);
s32 list_menu_actor_records_with_primary(void **records);
s32 list_menu_linked_actor_records(void **records);

typedef struct MenuEntryTemplate {
    s32 words[4];
} MenuEntryTemplate;

typedef struct MenuEntryCommon {
    s32 word0, word1, word2;
} MenuEntryCommon;

typedef struct MenuEntryState {
    void (*callback)(struct MenuEntryState *, void *, void *, void *);
    u8 pad_04[0x5C];
    MenuEntryTemplate display_template;
    MenuEntryCommon linked_common;
    MenuEntryCommon entry_common;
    u8 display_owner[0x0C];
    s32 entry_value;
    void **entries;
    u16 *resources[1];
} MenuEntryState;

typedef struct MenuEntryObject {
    ObjectNodeHeader node;
    MenuEntryState state;
} MenuEntryObject;

s32 prepare_cached_menu_entries(MenuEntryState *state, s32 count);
s32 link_cached_menu_entries(void **entries);
void initialize_cached_menu_entry(MenuEntryState *state, s32 resource_id, s32 slot_index, s32 x, s32 y, s32 z);
void invoke_cached_menu_callback(MenuEntryState *state, void *position, void *sprite, void *context);
int draw_tinted_node_sprites_scratch(void *forwarded_ptr, int unused_arg, void *second_ptr);
void register_node(MenuEntryObject *object, void (*draw)(void *, s32, void *));
void release_null_terminated_entries(u16 **resources);
MenuEntryObject *allocate_menu_entry_object(s32 resource_id, s32 slot_index, s32 x, s32 y, s32 z);
void clear_menu_entries(void **entries);
void release_menu_entry_state(MenuEntryState *state);
void release_menu_entry_object(MenuEntryObject *object);
void *allocate_menu_pair(void *first, void *second, s32 mode);
void *allocate_menu_pair_default(void *first, void *second);

typedef struct MenuPanelTransform {
    u8 pad_00[6];
    s16 scale;
} MenuPanelTransform;

typedef struct MenuPanelChildren {
    u8 pad_00[0x98];
    void *colors[2];
} MenuPanelChildren;

typedef struct MenuPanelState {
    u8 pad_00[8];
    s32 step;
    u8 pad_0C[0x18];
    u8 tagged_stream[0x80];
    MenuPanelTransform *transform;
    u8 pad_A8[8];
    MenuPanelChildren *children;
} MenuPanelState;

typedef struct MenuPanelUpdateRecord {
    void (*update)(MenuPanelState *);
    u8 pad_04[12];
    MenuPanelState state;
} MenuPanelUpdateRecord;

void advance_timed_tagged_stream(void *stream);
void fade_color_to_gray(void *object, s32 unused);
void handle_menu_panel_input(MenuPanelState *state);
void update_menu_panel_colors(MenuPanelState *state);
void advance_menu_panel_scale(void *record);

extern MenuEntryCommon menu_entry_common_template;
extern u8 menu_entry_link_table[];
void set_entry_common_pointers(void **entries, MenuEntryCommon *common, s32 count);
s32 build_reverse_indexed_chain(void **entries, void *table, s32 count);
void initialize_menu_display_templates(void *owner, MenuEntryTemplate *display, MenuEntryCommon *common, s32 x, s32 y, s32 z);
void clear_cached_menu_entry(MenuEntryState *state);
void set_cached_menu_entry_resource(MenuEntryState *state, s32 resource_id, s32 slot_index);

#endif
