#ifndef DUNGEON_MENU_CACHE_ACTOR_CHOICE_H
#define DUNGEON_MENU_CACHE_ACTOR_CHOICE_H

#include "dungeon/menu_cache_close.h"
#include "engine/menu/animated_selection_body.h"
#include "shared/menu_display.h"

/* The two actor selectors have different node bodies and the same linked actor list. */
typedef struct CachedActorChoice {
    void (*animate)(struct CachedActorChoice *choice);
    AnimatedSelectionEntry *entries[2];
    void *actors[2];
    s32 choice_mode;
    s32 actor_count;
    s32 transition_frames;
    s32 transition_tick;
    s32 selected_index;
    s32 previous_index;
    s32 spacing;
    s32 origin_y;
    s32 repeat_ticks;
    s32 directional_enabled;
    ObjectNodeHeader *owner;
} CachedActorChoice;

typedef struct CachedActorMessage {
    ObjectNodeHeader *owner;
} CachedActorMessage;

typedef struct CachedFamiliarBehaviorPackets {
    CachedStoragePanelPacket backdrop;
    SpritePartTexture labels[5];
} CachedFamiliarBehaviorPackets;

/* Chooses one of five behavior modes for the selected familiar. */
typedef struct CachedFamiliarBehaviorPanel {
    ObjectNodeHeader *owner;
    ActorRecord *actor;
    FrameState cursor;
    s32 cursor_idle;
    u8 pad_18[8];
    s32 transition_frames;
    s32 transition_tick;
    s32 selected_mode;
    s32 previous_mode;
    s32 repeat_delay;
    u8 highlight[5];
    u8 pad_39[3];
    CachedFamiliarBehaviorPackets *packets;
    ItemMenuDisplayBlock display;
    ItemMenuDisplayPosition position;
    DisplayPositionWords part_vectors;
    ItemMenuDisplayLinks links;
    ItemMenuPart *draw_chain;
    ItemMenuPart **parts;
    u16 *resources[12];
} CachedFamiliarBehaviorPanel;

/* The sprite renderer reads three angles followed by three signed translations. */
typedef struct CachedMenuPartTransform {
    s16 rotation_x;
    s16 rotation_y;
    s16 rotation_z;
    s16 x;
    s16 y;
    s16 z;
} CachedMenuPartTransform;

typedef struct CachedPartyChoice {
    void (*animate)(struct CachedPartyChoice *choice);
    void (*after_animate)(struct CachedPartyChoice *choice);
    s32 focus_ticks;
    s32 focus_step;
    s32 focus_column;
    s32 pending_delta;
    AnimatedSelectionEntry *entries[2];
    void *actors[2];
    s32 actor_count;
    s32 transition_frames;
    s32 transition_tick;
    s32 selected_index;
    s32 previous_index;
    s32 repeat_ticks;
    s32 spacing;
    s32 directional_enabled;
    ObjectNodeHeader *owner;
} CachedPartyChoice;

static inline void fill_cached_choice_actors(void **actors, s32 *count)
{
    *count = list_menu_linked_actor_records(actors);
}

void initialize_actor_choice(CachedActorChoice *choice);
s32 find_actor_choice(CachedActorChoice *choice, s32 actor_index);
void shade_actor_choices(CachedActorChoice *choice);

void initialize_party_choice(CachedPartyChoice *choice);
s32 find_party_choice(CachedPartyChoice *choice, s32 actor_index);
void shade_party_choices(CachedPartyChoice *choice);

void idle_actor_choice(CachedActorChoice *choice);
void reorder_actor_choices(CachedActorChoice *choice);
void begin_actor_choice_change(CachedActorChoice *choice, s32 delta);
void poll_actor_choice_input(CachedActorChoice *choice);
void update_actor_choice(CachedActorChoice *choice);

/* These entries retain the status node's renderable header. */
void release_actor_choice(ObjectNodeHeader *node);
ItemMenuPart *link_familiar_behavior_parts(ItemMenuPart **parts);
extern char cached_actor_message_text[];
void set_cached_actor_preview_target(ObjectNodeHeader *owner, s32 actor_index);

void idle_party_choice(CachedPartyChoice *choice);
void reorder_party_choices(CachedPartyChoice *choice);
ObjectNodeHeader *begin_party_choice_change(CachedPartyChoice *choice, s32 delta);
ObjectNodeHeader *refresh_party_choice_preview(ObjectNodeHeader *owner);
s32 get_party_preview_mode(ObjectNodeHeader *owner);
void update_party_preview_target(ObjectNodeHeader *owner, s32 actor_index);
void resume_party_choice_transition(CachedPartyChoice *choice);
void poll_party_choice_input(CachedPartyChoice *choice);
void update_party_choice(CachedPartyChoice *choice);
s32 get_party_choice_selection(ObjectNodeHeader *node);
void enable_party_choice_input(ObjectNodeHeader *node);
void disable_party_choice_input(ObjectNodeHeader *node);
void ease_cached_party_choice_focus(CachedPartyChoice *choice);
void start_party_choice_focus(ObjectNodeHeader *node, s32 column);
ActorRecord *get_party_choice_actor(ObjectNodeHeader *node);

/* Both selectors use the same directional repeat and actor shortcuts. */
#define READ_CACHED_CHOICE_DIRECTION(choice, input, delta) do { \
    s32 repeat_ticks; \
    s32 held_buttons; \
 \
    if (choice->directional_enabled && (input->buttons & 0xa000)) { \
        if (input->pressed_buttons & 0x2000) { \
            delta = 1; \
            choice->repeat_ticks = 0; \
            choice->transition_frames = 4; \
        } else if (input->pressed_buttons & 0x8000) { \
            delta = -1; \
            choice->repeat_ticks = 0; \
            choice->transition_frames = 4; \
        } else { \
            repeat_ticks = choice->repeat_ticks; \
            if (repeat_ticks >= 9) { \
                choice->repeat_ticks = repeat_ticks - 2; \
                held_buttons = input->buttons; \
                if (held_buttons & 0x2000) { \
                    delta = 1; \
                    choice->transition_frames = 3; \
                } else if (held_buttons & 0x8000) { \
                    delta = -1; \
                    choice->transition_frames = 3; \
                } \
            } else { \
                choice->repeat_ticks = repeat_ticks + 1; \
            } \
        } \
    } \
    if (delta == 0) { \
        if (input->pressed_buttons & 1) { \
            if (choice->selected_index != 0) { \
                choice->transition_frames = 4; \
                delta = -1; \
            } \
        } else if (input->pressed_buttons & 2) { \
            if (choice->actor_count == 2 && choice->selected_index != 1) { \
                choice->transition_frames = 4; \
                delta = 1; \
            } \
        } \
    } \
} while (0)

s32 initialize_actor_choice_entries(CachedActorChoice *choice);
ObjectNodeHeader *create_actor_choice(ObjectNodeHeader *owner, s32 actor_index, s32 mode,
                                             s32 origin_y, s32 directional_enabled);
ObjectNodeHeader *create_fusion_actor_selector(ObjectNodeHeader *owner, s32 actor_index, s32 origin_y);
void poll_cached_actor_message_cancel(CachedActorMessage *message);
void start_cached_actor_message_transition(CachedActorMessage *message);
void poll_cached_actor_message_switch(CachedActorMessage *message);
ObjectNodeHeader *create_cached_actor_message(ObjectNodeHeader *owner);

void poll_familiar_behavior_panel(CachedFamiliarBehaviorPanel *panel);
void update_familiar_behavior_motion(CachedFamiliarBehaviorPanel *panel);
void bind_familiar_behavior_vectors(ItemMenuPart **parts, DisplayPositionWords **banks,
                                             DisplayPositionWords *common);
extern SpritePartCommand cached_behavior_header_graphic[];
extern SpritePartCommand cached_behavior_row_graphic[];
extern FrameNode cached_behavior_cursor_template;

void style_familiar_behavior_row(ItemMenuPart *part, ItemMenuPart *label, s32 index, s32 highlight);
void confirm_familiar_behavior(ObjectNodeHeader *node);
void advance_familiar_behavior_opening(CachedFamiliarBehaviorPanel *panel);
void populate_familiar_behavior_labels(CachedFamiliarBehaviorPanel *panel);
void initialize_familiar_behavior_display(CachedFamiliarBehaviorPanel *panel,
                                                  ItemMenuDisplayLinks *links,
                                                  ItemMenuDisplayBlock *display,
                                                  ItemMenuDisplayPosition *position);
void position_familiar_behavior_cursor(CachedFamiliarBehaviorPanel *panel, s32 mode);
void initialize_familiar_behavior_parts(CachedFamiliarBehaviorPanel *panel);
void initialize_familiar_behavior_request(CachedFamiliarBehaviorPanel *panel, ObjectNodeHeader *owner, ActorRecord *actor);
void configure_familiar_behavior_panel(CachedFamiliarBehaviorPanel *panel, ObjectNodeHeader *owner, ActorRecord *actor);
s32 prepare_familiar_behavior_parts(CachedFamiliarBehaviorPanel *panel, s32 count);

void position_cached_actor_choice_entries(CachedActorChoice *choice);

void position_cached_party_choice_entries(CachedPartyChoice *choice);
s32 compare_selection_menu_entry_order_for_party(u8 *left, u8 *right);

extern const char *const cached_familiar_behavior_descriptions[5];


extern const s16 cached_party_focus_targets[2][2];

#endif
