#ifndef DUNGEON_OVL_FA7000_H
#define DUNGEON_OVL_FA7000_H
#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/system.h"
#include "engine/node/allocation.h"
struct ObjectNodeHeader;
struct SpriteFrameState;
extern u8 zu_default_frames[];
void select_sprite_entry();
void func_80047784();
s32 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
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
s32 register_node(struct ObjectNodeHeader *entry, void *registration_id);
s32 func_8004491C(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
void *spawn_zu_actor(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
void update_bank_actor_movement(void *entity, void *motion_arg, void *sprite_arg);
void update_bank_actor_state(ActorRecord *actor, ObjectPosition *context, struct SpriteFrameState *sprite, ActorRecord *stats_in);
void advance_bank_actor_path(void *motion, void *context, void *entity, void *path_state);
void select_bank_actor_movement(ActorRecord *move_data, void *context, TileObject *position_data, ActorRecord *actor_data);
s32 begin_bank_directional_effect(ActorRecord *action_state, void *motion_param, struct SpriteFrameState *sprite, ActorRecord *actor);
void initialize_bank_actor_action(ActorRecord *action_state, s32 motion_param, struct SpriteFrameState *sprite, ActorRecord *entity);
s32 complete_actor_jump_to_destination(ActorRecord *actor, void *primary_context, void *secondary_context, s32 force_move);
void select_bank_resident_callback(ActorRecord *state, ObjectPosition *motion, struct SpriteFrameState *source, ActorRecord *target);
void select_bank_actor_callback(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void update_bank_staged_movement(void *action, void *motion,struct SpriteFrameState *map_actor, void *actor_arg);
void update_bank_actor_targeted_action(void *owner_input, ObjectPosition *motion_input, struct SpriteFrameState *actor_input, ActorRecord *object);
void restore_bank_actor_tile(void *action, ObjectPosition *motion, void *sprite, EntityRec *entity);
void slow_directional_motion(void *effect_data, void *motion_data, void *sprite_data, void *object_data);
void forward_bank_actor_callback_a(void *state, s32 action, struct SpriteFrameState *source, EntityRec *target);
void forward_bank_actor_callback_b(void *state, s32 action, struct SpriteFrameState *source, EntityRec *target);
void restore_bank_actor_callback_a(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void handle_actor_action_effects(void *controller, ObjectPosition *motion, void *sprite, ActorRecord *actor);
void advance_bank_actor_animation(void *controller, void *context, void *sprite, void *entity);
void update_bank_actor_sprite_state(ActorRecord *actor, ObjectPosition *action, struct SpriteFrameState *sprite, ActorRecord *target);
void update_directional_sprite_state_and_signals(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void restore_bank_actor_callback_b(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void restore_bank_actor_callback_c(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void restore_bank_actor_callback_d(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void update_bank_effect_fade(void *effect, MovingPosition *position, struct SpriteFrameState *visual);
void start_bank_actor_hit_reaction(void *work, void *part_a,struct SpriteFrameState *part_b, ActorRecord *actor);
void update_bank_timed_effect(void *state_input, void *motion_input, void *animation_input, void *actor_input);
void create_cylindrical_effect(void *state);
#endif
