#ifndef DUNGEON_MENU_CACHE_LINKED_ACTOR_H
#define DUNGEON_MENU_CACHE_LINKED_ACTOR_H

#include "dungeon/menu_cache_close.h"

/* The factory stores these two children before installing the menu callbacks. */
typedef struct CachedLinkedActorMenu {
    CachedMenuOwnerLink owner_link;
    s32 preserve_owner;
    ObjectNodeHeader *actor_choice;
    ObjectNodeHeader *command_panel;
} CachedLinkedActorMenu;

/* The 50-part command panel uses two controls and four groups of twelve rows. */
typedef struct CachedLinkedActorPanel {
    ObjectNodeHeader *owner;
    void *panel_packets;
    u8 pad_08[3];
    /* The first slot stays zero for the disabled row. Choices start at one. */
    u8 action_ids[13];
    u8 row_highlight[12];
    u16 saved_action_flags[2];
    s16 action_count;
    s16 ability_count;
    s16 has_primary_action;
    s16 has_secondary_action;
    s16 transition_frames;
    s16 transition_tick;
    s16 selected_row;
    s16 previous_row;
    s16 repeat_delay;
    s16 opening_step;
    s32 actor_index;
    ActorRecord *actor;
    ItemMenuDisplayBlock display;
    ItemMenuDisplayPosition position;
    DisplayPositionWords part_vectors;
    ItemMenuDisplayLinks links;
    ItemMenuPart *draw_chain;
    ItemMenuPart **parts;
    u16 *resources[12];
} CachedLinkedActorPanel;

typedef struct CachedActorActionText {
    s16 species;
    s16 variant;
    const char *description;
    const char *label;
} CachedActorActionText;

extern u8 cached_no_linked_actor_notice[];
extern const char cached_linked_actor_strings[];
extern CachedActorActionText cached_linked_actor_action_text[28];

void show_cached_linked_actor_notice(void);
void initialize_linked_actor_panel_packets(void *packets);
void poll_cached_linked_actor_cancel(void *body);
void check_cached_linked_actor_close_signal(void *body);
void release_cached_linked_actor_children(CachedLinkedActorMenu *menu);
void *ensure_cached_linked_actor_close(CachedMenuOwnerLink *link);
void start_cached_linked_actor_close(CachedLinkedActorMenu *menu);
void finish_cached_linked_actor_cleanup(CachedLinkedActorMenu *menu);
ObjectNodeHeader *create_linked_actor_menu(ObjectNodeHeader *owner, s32 position, s32 preserve_owner);
ObjectNodeHeader *open_linked_actor_menu(ObjectNodeHeader *owner, s32 position);
ObjectNodeHeader *create_linked_actor_submenu(ObjectNodeHeader *owner, s32 position);
ObjectNodeHeader *create_cached_linked_actor_selector(ObjectNodeHeader *owner, s32 position);
ObjectNodeHeader *create_cached_linked_actor_panel(ObjectNodeHeader *owner, s32 position);
void release_cached_linked_actor_panel(ObjectNodeHeader *node);
void update_selection_tile_markers(ActorRecord *entity, s32 selection);
void begin_actor_command_update(ObjectNodeHeader *panel, s32 actor_index);
void reset_actor_command_panel(ObjectNodeHeader *panel);
void set_cached_actor_preview_target(ObjectNodeHeader *node, s32 actor_index);
void reset_cached_linked_actor_preview(ObjectNodeHeader *node);
const CachedActorActionText *find_cached_actor_action_text(const ActorRecord *actor, s32 variant);
const char *get_cached_actor_action_label(const ActorRecord *actor, s32 variant);
const char *get_cached_actor_action_description(const ActorRecord *actor, s32 variant);
ItemMenuPart *link_cached_actor_grid_parts(ItemMenuPart **parts);
ItemMenuPart *link_cached_actor_panel_parts(ItemMenuPart **parts);

void update_cached_actor_command_row_motion(CachedLinkedActorPanel *panel);
void schedule_cached_linked_actor_close(ObjectNodeHeader *node);
void schedule_cached_linked_actor_cleanup(ObjectNodeHeader *node);
s32 find_actor_command_row(CachedLinkedActorPanel *panel, ActorRecord *actor);
void poll_actor_command_panel(CachedLinkedActorPanel *panel);
void finish_actor_command_grid_opening(CachedLinkedActorPanel *panel);
void animate_actor_command_change(CachedLinkedActorPanel *panel);
void apply_actor_command(CachedLinkedActorPanel *panel);
void initialize_cached_actor_command_request(CachedLinkedActorPanel *panel, ObjectNodeHeader *owner, s32 actor_index);
void initialize_actor_command_row_layout(CachedLinkedActorPanel *panel);
void bind_actor_command_part_vectors(ItemMenuPart **parts, DisplayPositionWords **buffers,
                                            DisplayPositionWords *common);
void *get_menu_count_template(s32 count);
extern const char *const cached_actor_command_descriptions[6];

void reset_actor_command_row_positions(CachedLinkedActorPanel *panel);
s32 is_actor_command_input_disabled(ActorRecord *actor);
void run_actor_command_input(CachedLinkedActorPanel *panel);
void advance_actor_command_grid_opening(CachedLinkedActorPanel *panel);
s32 prepare_actor_command_parts(CachedLinkedActorPanel *panel, s32 count);
void initialize_actor_command_background(CachedLinkedActorPanel *panel, ItemMenuDisplayLinks *links,
                                                ItemMenuDisplayBlock *display, ItemMenuDisplayPosition *position);
void *create_actor_command_description(s32 action, ActorRecord *actor);
void populate_actor_command_descriptions(CachedLinkedActorPanel *panel, ActorRecord *actor);
s32 build_actor_command_options(CachedLinkedActorPanel *panel, u8 *actions, ActorRecord *actor);
s32 count_actor_command_abilities(ActorRecord *actor);
void configure_actor_command_panel(CachedLinkedActorPanel *panel, ObjectNodeHeader *owner, s32 actor_index);
void clear_actor_command_labels(CachedLinkedActorPanel *panel);
void clear_actor_command_parts(CachedLinkedActorPanel *panel);
void restart_actor_command_panel(CachedLinkedActorPanel *panel);

const char *get_actor_command_hint(s32 action, ActorRecord *actor);
s16 resolve_alternate_spell_id(s32 tile_index);
extern const char *const cached_actor_direct_attack_hint;
extern const char *const cached_actor_current_direction_move_hint;
extern const char *const cached_actor_stay_hint;
extern const char *const cached_actor_command_unavailable_hint;

void save_cached_linked_actor_action_flags(CachedLinkedActorPanel *panel);
void restore_cached_linked_actor_action_flags(CachedLinkedActorPanel *panel);

#endif
