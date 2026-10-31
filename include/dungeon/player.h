#ifndef DUNGEON_PLAYER_H
#define DUNGEON_PLAYER_H

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

void begin_actor_turn_toward_target(ActorRecord *body, void *unused, void *actor, ActorRecord *motion);
s32 begin_familiar_command_selection(Rec_func_8008D024_arg0 *actor, void *context, SpriteFrameState *display, s32 target_index, s32 action_mode);
s32 begin_familiar_summoning(void *record, s32 input1, void *pointer_input, s32 value_input);
void apply_pending_byte_increase(void *unused_0, void *unused_1, void *unused_2, ActorRecord *object);
void begin_player_damage_reaction(void *action, void *unused, void *sprite, ActorRecord *actor);
void begin_player_pickup_animation(u8 *actor, s32 effect_arg, u8 *target, u8 *source);
void begin_player_sleep_action(void *record, void *unused, void *object, ActorRecord *entity);
void begin_player_wait_turn(ActorRecord *state, void *mode, void *sprite, ActorRecord *entity);
s32 begin_selected_target_level_up(ActorRecord *actor_state, void *action_arg, void *sprite, ActorRecord *target);
s32 begin_target_flagged_action(void *actor, s32 action_arg, s32 unused, ActorRecord *target);
void begin_wake_nearby_monsters(u8 *state_ptr, void *value, u8 *target_ptr, u8 *angle_ptr);
void clear_player_linked_action_flags(void);
s32 dispatch_dungeon_category_action(void *actor, void *action, s16 dispatch_mode, s32 handler_param);
s32 reject_forbidden_familiar_recall(s32 entry_index);
void select_state_16_directional_animation(void *entity, void *unused, void *animation, ActorRecord *state);
void set_familiar_formation_offset(s32 entry_index, s8 value);
void set_linked_actor_code_and_mirror(s16 object_index, s8 value);
void set_linked_actor_pending_halfword(s32 entry_index, s32 value);
void update_player_height_step(void *actor, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *model);



struct Rec_func_8008ACDC_arg0;
struct S_8008CD4C_2;
void begin_player_push(struct Rec_func_8008ACDC_arg0 *action, s32 context, SpriteFrameState *sprite, struct S_8008CD4C_2 *actor,
    s16 move_state);
void process_dungeon_menu_selection(void *state, s32 context, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_hop_and_return(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void update_player_push(void *actor, void *motion, SpriteFrameState *sprite, void *model);

void update_active_nodes_and_render_frame(void);
void queue_framebuffer_strip_quads(void);
void dispatch_object_renderers(void);


void begin_parameterized_actor_action(void *object, void *unused_1, void *unused_2, void *word_value, s32 halfword_value);

void begin_player_menu_action(void *actor, void *unused_1, void *unused_2, void *action_value);

void begin_player_trap_trigger(void *object, void *unused_1, void *unused_2, void *shared_value);

void create_familiar_deployment_overlay(void *owner_body, ObjectPosition *source_pos, SpriteFrameState *owner);

void begin_player_jump(struct Rec_func_8008ACDC_arg0 *state, void *unused, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct DungeonItemEntry;
void equip_item_and_update_status(ActorRecord *context, DungeonItemEntry *item);

struct S_80098614_0;
void change_equipped_item_and_notify(struct S_80098614_0 *actor, struct DungeonItemEntry *requested_item);

void restore_player_control_callback(void *target, void *source);

s16 get_special_table_data_index(s32 dataAddress);

void resolve_familiar_deployment_request(void *context_ptr, s32 unused_one, void *unused_two, void *selection_ptr);
s32 reveal_triggered_trap(void *actor);
void store_recalled_familiar(s32 slot_table, void *unused_arg1, void *unused_arg2, EntityRec *owner);

#endif
