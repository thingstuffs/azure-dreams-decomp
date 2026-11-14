#ifndef DUNGEON_PLAYER_H
#define DUNGEON_PLAYER_H

struct MovingTile;

/* Function contracts owned by src/dungeon/player/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "records/Rec_func_8008D024_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_item_entries.h"
#include "records/Rec_func_8008ACDC_arg0.h"
/* Sparse view of the player's familiar-item address slots. Input and recall
 * paths form player_base + slot * 4 before reading +0xD0. Restore writes the
 * corresponding save-page item address, and detachment clears that word.
 * Preserve the signed integer address representation and all byte indexing;
 * this projection is not an array element or the complete PlayerRecord tail. */
typedef struct FamiliarItemSlotView {
    u8 pad_00[0xD0];
    s32 item_address;
} FamiliarItemSlotView;

void begin_actor_turn_toward_target(ActorRecord *body, ObjectPosition *unused, void *actor, ActorRecord *motion);
s32 begin_familiar_command_selection(Rec_func_8008D024_arg0 *actor, ObjectPosition *context, SpriteFrameState *display, s32 target_index, s32 action_mode);
s32 begin_familiar_summoning(ActorRecord *record, s32 input1, void *pointer_input, s32 value_input);
void apply_pending_byte_increase(void *unused_0, void *unused_1, void *unused_2, ActorRecord *object);
void begin_player_damage_reaction(void *action, ObjectPosition *unused, void *sprite, ActorRecord *actor);
void begin_player_pickup_animation(ActorRecord *actor, s32 effect_arg, u8 *target, ActorRecord *source);
void begin_player_sleep_action(void *record, ObjectPosition *unused, void *object, ActorRecord *entity);
void begin_player_wait_turn(ActorRecord *state, ObjectPosition *mode, void *sprite, ActorRecord *entity);
s32 begin_selected_target_level_up(ActorRecord *actor_state, void *action_arg, void *sprite, ActorRecord *target);
s32 begin_target_flagged_action(void *actor, s32 action_arg, SpriteFrameState *unused, ActorRecord *target);
void begin_wake_nearby_monsters(ActorRecord *state_ptr, void *value, u8 *target_ptr, u8 *angle_ptr);
void clear_player_linked_action_flags(void);
s32 dispatch_dungeon_category_action(void *actor, void *action, s16 dispatch_mode, s32 handler_param);
s32 reject_forbidden_familiar_recall(s32 entry_index);
void select_player_motion_animation(void *entity, ObjectPosition *unused, void *animation, ActorRecord *state);
void set_familiar_formation_offset(s32 entry_index, s8 value);
void set_linked_actor_code_and_mirror(s16 object_index, s8 value);
void set_linked_actor_pending_value(s32 entry_index, s32 value);
void update_player_height_step(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *model);



struct Rec_func_8008ACDC_arg0;
struct S_8008CD4C_2;
void begin_player_push(struct Rec_func_8008ACDC_arg0 *action, s32 context, SpriteFrameState *sprite, struct S_8008CD4C_2 *actor,
    s16 move_state);
void process_dungeon_menu_selection(void *state, s32 context, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_hop_and_return(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void update_player_push(ActorRecord *actor, void *motion, SpriteFrameState *sprite, ActorRecord *model);

void update_active_nodes_and_render_frame(void);
void queue_framebuffer_strip_quads(void);
void dispatch_object_renderers(void);


void begin_parameterized_actor_action(void *object, void *unused_1, void *unused_2, void *word_value, s32 halfword_value);

void begin_player_menu_action(void *actor, ObjectPosition *unused_1, SpriteFrameState *unused_2, void *action_value);

void begin_player_trap_trigger(void *object, void *unused_1, void *unused_2, void *shared_value);

void create_familiar_deployment_overlay(void *owner_body, ObjectPosition *source_pos, SpriteFrameState *owner);
void update_familiar_deployment_change(ActorRecord *actor, ObjectPosition *map, SpriteFrameState *entity, ActorRecord *context);
void update_familiar_deployment_overlay(void *object_data, ObjectPosition *unused, SpriteFrameState *sprite_data);

void begin_player_jump(struct Rec_func_8008ACDC_arg0 *state, void *unused, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct DungeonItemEntry;
void equip_item_and_update_status(ActorRecord *context, DungeonItemEntry *item);

struct S_80098614_0;
void change_equipped_item_and_notify(ActorRecord *actor, struct DungeonItemEntry *requested_item);

void restore_player_control_callback(void *target, void *source);

s16 get_item_slot_number(s32 dataAddress);

void resolve_familiar_deployment_request(void *context_ptr, s32 unused_one, void *unused_two, void *selection_ptr);
s32 reveal_triggered_trap(void *actor, s32 unused_context_a, s32 unused_context_b, s32 unused_target);
void store_recalled_familiar(s32 slot_table, void *unused_arg1, void *unused_arg2, ActorRecord *owner);


void update_familiar_command_selection(ActorRecord *state, s32 context_a, SpriteFrameState *sprite, ActorRecord *actor);
void update_floor_exit_transition(PlayerRecord *state, ObjectPosition *unused_position, struct MovingTile *tile, ActorRecord *actor);

void advance_actor_death_transition(ActorRecord *context, ObjectPosition *unused, SpriteFrameState *input, ActorRecord *entity);

void advance_category_action_callback(ActorRecord *object, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *context);

void finish_player_action_animation(ActorRecord *target, ObjectPosition *unused, SpriteFrameState *flag_data, ActorRecord *source);

#endif
