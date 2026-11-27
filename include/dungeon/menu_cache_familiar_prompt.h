#ifndef DUNGEON_MENU_CACHE_FAMILIAR_PROMPT_H
#define DUNGEON_MENU_CACHE_FAMILIAR_PROMPT_H

#include "dungeon/menu_cache_close.h"
#include "dungeon/menu_cache_selection.h"
#include "engine/menu/entry_words.h"
#include "sdk/libgpu_types.h"
#include "shared/sprite_frame_state.h"
#include "shared/sprite_part_command.h"

struct CachedFamiliarPromptPackets;

/* The prompt creator allocates the 27 part pointers and their backing resources. */
typedef struct CachedFamiliarPrompt {
    s32 opening_step;
    s32 repeat_delay;
    s32 selected_actor_index;
    s32 actor_count;
    s32 current_page;
    s32 last_page;
    s32 input_enabled;
    s32 assignment_slot;
    s32 available_slots;
    u8 pad_24[0xc];
    ActorRecord *actors[20];
    ActorRecord *selected_actor;
    ObjectNodeHeader *owner;
    struct CachedFamiliarPromptPackets *packets;
    StorageDisplayBlock display;
    ItemMenuDisplayPosition position;
    DisplayPositionWords part_common;
    ItemMenuDisplayLinks links;
    ItemMenuPart *draw_chain;
    ItemMenuPart **parts;
    u16 *resources[9];
    void *previous_update;
} CachedFamiliarPrompt;

typedef struct CachedFamiliarPromptNode {
    ObjectNodeHeader header;
    CachedFamiliarPrompt prompt;
} CachedFamiliarPromptNode;

typedef struct CachedFamiliarPromptFlow {
    CachedMenuOwnerLink owner_link;
    MenuEntryObject *actor_status;
    CachedFamiliarPromptNode *prompt;
} CachedFamiliarPromptFlow;

typedef struct CachedFamiliarPromptFlowNode {
    ObjectNodeHeader header;
    CachedFamiliarPromptFlow flow;
} CachedFamiliarPromptFlowNode;

ItemMenuPart *link_cached_action_parts(ItemMenuPart **parts);
ItemMenuPart *link_familiar_prompt_parts(ItemMenuPart **parts);
void release_familiar_prompt_labels(ItemMenuPart **parts);
void release_familiar_prompt(CachedFamiliarPromptNode *node);
ActorRecord *get_familiar_prompt_selected_actor(CachedFamiliarPromptNode *node);
void enable_familiar_prompt_input(CachedFamiliarPromptNode *node);
void disable_familiar_prompt_input(CachedFamiliarPromptNode *node);
ObjectNodeHeader *create_cached_familiar_prompt_flow(ObjectNodeHeader *owner, s32 index);
void release_familiar_prompt_flow_children(CachedFamiliarPromptFlow *flow);
void *ensure_familiar_prompt_close(CachedMenuOwnerLink *link);
void start_familiar_prompt_close(CachedFamiliarPromptFlow *flow);
void schedule_familiar_prompt_close(ObjectNodeHeader *node);
ObjectNodeHeader *release_familiar_prompt_owner(ObjectNodeHeader *header);
void finish_familiar_prompt_close(CachedFamiliarPromptFlow *flow);
void schedule_familiar_prompt_cleanup(ObjectNodeHeader *node);
MenuEntryObject *get_familiar_prompt_actor_status(ObjectNodeHeader *node);
void enable_familiar_prompt_flow_input(ObjectNodeHeader *node);
void disable_familiar_prompt_flow_input(ObjectNodeHeader *node);

typedef struct CachedFamiliarPromptCoordinate {
    s32 coordinate;
} CachedFamiliarPromptCoordinate;

s32 find_familiar_prompt_actor(ActorRecord **actors, ActorRecord *actor, s32 count);
s32 prepare_familiar_prompt(CachedFamiliarPrompt *prompt, s32 count);
void initialize_familiar_prompt_request(CachedFamiliarPrompt *prompt, ObjectNodeHeader *owner, ActorRecord *actor);
void populate_familiar_prompt_parts(CachedFamiliarPrompt *prompt, ItemMenuPart **parts);
void configure_familiar_prompt_links(CachedFamiliarPrompt *prompt, ItemMenuDisplayLinks *links,
                                          StorageDisplayBlock *block, ItemMenuDisplayPosition *vector,
                                          CachedFamiliarPromptCoordinate x, CachedFamiliarPromptCoordinate y);
void setup_familiar_prompt(CachedFamiliarPrompt *prompt, ObjectNodeHeader *owner, ActorRecord *actor, s32 x, s32 y);

typedef struct CachedFamiliarCursorShape {
    u8 flags;
    u8 command;
    s8 x;
    s8 y;
    u8 red;
    u8 green;
    u8 blue;
    u8 color_flags;
    u8 unused[2];
    u8 width;
    u8 height;
} CachedFamiliarCursorShape;

typedef struct CachedFamiliarBackdrop {
    PrimitivePairEntry lines[2];
    u8 gradient[0x44];
} CachedFamiliarBackdrop;

void initialize_familiar_cursor_shape(CachedFamiliarCursorShape *shape);
void set_familiar_previous_page(ItemMenuPart **parts, s32 show);
void set_familiar_next_page(ItemMenuPart **parts, s32 show);
void position_familiar_prompt_cursors(ItemMenuPart **parts, s32 index);
void build_familiar_backdrop(CachedFamiliarBackdrop *backdrop);
void update_familiar_prompt_page(ItemMenuPart **parts, CachedFamiliarPrompt *prompt);
extern u8 cached_familiar_fainted_text[];
extern SpritePartTexture cached_familiar_slot_one_button[];
extern SpritePartTexture cached_familiar_slot_two_button[];
SpritePartCommand *get_assigned_familiar_marker(s32 slot);

void populate_familiar_page_labels(ItemMenuPart **parts, CachedFamiliarPrompt *prompt);
void refresh_familiar_slot_markers(ItemMenuPart **parts, CachedFamiliarPrompt *prompt);
void update_familiar_prompt_description(CachedFamiliarPrompt *prompt);
void run_familiar_prompt_input(CachedFamiliarPrompt *prompt);
void advance_familiar_prompt_opening(CachedFamiliarPrompt *prompt);
void poll_familiar_prompt_input(CachedFamiliarPrompt *prompt);
void set_item_panel_height(void *packet, s32 height);
extern u8 cached_familiar_empty_description[];

void shade_familiar_slot(ItemMenuPart *part, s32 highlight);
void shade_familiar_assignment_slots(ItemMenuPart **parts, s32 slot);
s32 select_familiar_assignment_slot(ActorRecord *actor, s32 requested_slot, s32 available_mask);

struct CachedFamiliarPromptPackets {
    u8 pad_00[0x48];
    CachedFamiliarCursorShape cursor;
    CachedFamiliarBackdrop backdrop;
    u8 pad_B0[0x10];
    SpritePartTexture fainted_marker[1];
};

struct DungeonItemEntry;
ObjectNodeHeader *create_familiar_assignment_menu(ObjectNodeHeader *owner, s32 index, s32 mode,
                                                        s32 x, s32 y, struct DungeonItemEntry *item, s32 slot);
struct DungeonItemEntry *find_familiar_assignment_item(ActorRecord *actor);
ObjectNodeHeader *begin_familiar_assignment(CachedFamiliarPrompt *prompt);
void retry_familiar_assignment(CachedFamiliarPrompt *prompt);
s32 collect_familiar_actors(struct DungeonItemEntry **items, ActorRecord **actors);
void move_familiar_prompt_selection(CachedFamiliarPrompt *prompt, s32 index);
extern SpritePartCommand cached_available_slot_markers[2];

SpritePartCommand *get_familiar_slot_marker(s32 slot);
s32 find_familiar_assignment_actor(s32 slot, s32 fallback, s32 count, ActorRecord **actors);

CachedFamiliarPromptNode *create_familiar_prompt(ObjectNodeHeader *owner, ActorRecord *actor,
                                                        s32 x, s32 y);
CachedFamiliarPromptNode *open_familiar_prompt(ObjectNodeHeader *owner, ActorRecord *actor,
                                                      s32 x, s32 y);

#endif
