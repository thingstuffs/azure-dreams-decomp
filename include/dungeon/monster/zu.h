#ifndef DUNGEON_OVL_FA7000_H
#define DUNGEON_OVL_FA7000_H
#include "shared/bank_actor_state.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/dungeon_moving_views.h"
struct RegistrationNode;
struct SpriteFrameState;
extern u8 zu_default_frames[];
void select_sprite_entry();
void func_80047784();
s32 test_neighbor_position_relation();
/* This retail bank used the signed-halfword declaration. */
s16 sample_terrain_surface_height();
void update_map_cell_flags_with_item_limit();
void cycle_map_cell_flags();
s32 check_entity_relation();
s16 get_actor_height_difference();
s32 probe_directional_neighbor();
s32 apply_camera_offset_and_select_target();
void advance_status_timers();
void spend_actor_mp();
s32 begin_ready_actor_directional_action();
s32 get_rounded_facing_and_rounding_flag();
void * allocate_list_node();
void * func_8003FD64();
s32 register_node(struct RegistrationNode *entry, void *registration_id);
s32 func_8004491C(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
s32 play_sound_if_enabled();
void *spawn_zu_actor(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
void update_bank_actor_movement(void *entity, void *motion_arg, void *sprite_arg);
void update_bank_actor_state(void *actor, void *context, struct SpriteFrameState *sprite, void *stats_in);
void advance_bank_actor_path(void *motion, void *context, void *entity, void *path_state);
void select_bank_actor_movement(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, ActorRecord *actor_data);
s32 begin_bank_directional_effect(Rec_func_800A9E70_arg0 *action_state, void *motion_param, struct SpriteFrameState *sprite, ActorRecord *actor);
void initialize_bank_actor_action(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, struct SpriteFrameState *sprite, EntityRec *entity);
s32 complete_actor_jump_to_destination(ActorRecord *actor, void *primary_context, void *secondary_context, s32 force_move);
void select_bank_resident_callback(BankActorState *state, void *motion, SpriteFrameState *source, EntityRec *target);
void select_bank_actor_callback(BankActorState *state, s32 action, struct SpriteFrameState *source, EntityRec *target);
void update_bank_staged_movement(void *action, void *motion,struct SpriteFrameState *map_actor, void *actor_arg);
void update_bank_actor_targeted_action(void *owner_input, ObjectPosition *motion_input, struct SpriteFrameState *actor_input, ActorRecord *object);
void restore_bank_actor_tile(void *action, ObjectPosition *motion, void *sprite, EntityRec *entity);
void slow_directional_motion(void *effect_data, void *motion_data, void *sprite_data, void *object_data);
void forward_bank_actor_callback_a(void *state, s32 action, struct SpriteFrameState *source, EntityRec *target);
void forward_bank_actor_callback_b(void *state, s32 action, struct SpriteFrameState *source, EntityRec *target);
void restore_bank_actor_callback_a(BankActorState *state, s32 action, struct SpriteFrameState *source, EntityRec *target);
void handle_actor_action_effects(void *controller, EntityRec *motion, void *sprite, ActorRecord *actor);
void advance_bank_actor_animation(void *controller, void *context, void *sprite, void *entity);
void update_bank_actor_sprite_state(BankActorState *actor, void *action, struct SpriteFrameState *sprite, ActorRecord *target);
void update_directional_sprite_state_and_signals(BankActorState *state, s32 action, struct SpriteFrameState *source, ActorRecord *target);
void restore_bank_actor_callback_b(BankActorState *state, s32 action, struct SpriteFrameState *source, EntityRec *target);
void restore_bank_actor_callback_c(BankActorState *state, s32 action, struct SpriteFrameState *source, EntityRec *target);
void restore_bank_actor_callback_d(BankActorState *state, s32 action, struct SpriteFrameState *source, EntityRec *target);
void update_bank_effect_fade(void *effect, MovingPosition *position, struct SpriteFrameState *visual);
void start_bank_actor_hit_reaction(void *work, void *part_a,struct SpriteFrameState *part_b, EntityRec *actor);
void update_bank_timed_effect(void *state_input, void *motion_input, void *animation_input, void *actor_input);
void create_cylindrical_effect(void *state);
#endif
