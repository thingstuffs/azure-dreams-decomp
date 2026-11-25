#ifndef DUNGEON_MENU_CACHE_PARTY_MENU_H
#define DUNGEON_MENU_CACHE_PARTY_MENU_H

#include "dungeon/menu_cache_selection.h"

/* The menu factory allocates three child nodes and gives them the same owner. */
typedef struct CachedPartyMenu {
    ObjectNodeHeader *owner;
    ObjectNodeHeader *actor_choice;
    CachedSelectionPanelNode *command_panel;
    ObjectNodeHeader *command_state;
    ObjectNodeHeader *preview_controller;
    ObjectNodeHeader *behavior_panel;
    u8 pad_18[4];
    s32 preview_mode;
    s32 preserve_owner;
} CachedPartyMenu;

typedef struct CachedPartyCommandState {
    s32 command_marker;
    ObjectNodeHeader *owner;
} CachedPartyCommandState;

void idle_party_command_state(CachedPartyCommandState *state);
void mark_cached_secondary_node_for_removal(CachedPartyCommandState *state);
void complete_party_command_state_release(CachedPartyCommandState *state);
void set_party_command_marker(ObjectNodeHeader *node);

extern u8 cached_no_linked_actor_notice[];
void check_party_menu_close_signal(void *body);
ObjectNodeHeader *create_party_actor_choice(ObjectNodeHeader *owner, s32 actor_index);
CachedSelectionPanelNode *create_party_command_panel(ObjectNodeHeader *owner);
ObjectNodeHeader *create_party_command_state(ObjectNodeHeader *owner);
void release_party_actor_choice(ObjectNodeHeader *node);
void release_party_command_state(ObjectNodeHeader *node);
void release_party_menu_children(CachedPartyMenu *menu);

void show_party_menu_notice(void);
ObjectNodeHeader *create_party_menu(ObjectNodeHeader *owner, s32 actor_index, s32 preserve_owner);
ObjectNodeHeader *open_party_menu(ObjectNodeHeader *owner, s32 actor_index);
ObjectNodeHeader *open_party_submenu(ObjectNodeHeader *owner, s32 actor_index);
void *ensure_party_menu_close(CachedPartyMenu *menu);
void start_party_menu_close(CachedPartyMenu *menu);
void finish_party_menu_cleanup(CachedPartyMenu *menu);
void schedule_party_menu_cleanup(ObjectNodeHeader *node);

/* The resident preview controller owns its own object node layout. */
void *create_selection_menu_controller(s16 initialValue);
void switch_selected_preview(void *object, s16 new_index);
ObjectNodeHeader *create_familiar_behavior_panel(ObjectNodeHeader *owner, ActorRecord *actor);

void resume_party_menu(CachedPartyMenu *menu);
void finish_party_preview(CachedPartyMenu *menu);
void wait_for_party_preview_close(CachedPartyMenu *menu);
void open_party_preview(CachedPartyMenu *menu);
void prepare_party_preview(CachedPartyMenu *menu);
void open_party_behavior_panel(CachedPartyMenu *menu);
void schedule_party_menu_resume(ObjectNodeHeader *node);

#endif
