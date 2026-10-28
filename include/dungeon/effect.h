#ifndef DUNGEON_EFFECT_H
#define DUNGEON_EFFECT_H

/* Function contracts owned by src/dungeon/effect/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
void apply_effect_bonuses(s16 effect_id, s32 unused_arg, ActorRecord *record);
void *create_mode_configured_object(s16 mode, s32 part_b_byte_24, s32 part_b_byte_25, s32 part_a_value, s32 part_b_value);
void create_record_with_effect_callback(void);
void *create_actor_value_popup(s32 flags, void *source_data, s16 value, u16 callback_mode);
void dispatch_target_action(u8 *actor, s32 action_context, u8 *destination, u8 *target);
void emit_scattered_effects_unless_blocked(void *source);
void process_nearby_object_midpoint(u8 *start_obj, u8 *end_obj, s16 start_height, s16 end_height, s16 call_param, s32 call_arg);
void run_indexed_callback_list(s16 list_index);
void spawn_directed_and_scattered_particles(s32 x, s32 y, s32 z);
void *spawn_randomized_particle_burst(s16 x, s16 y, s16 z, s32 sprite_data, u16 sprite_id, s16 play_sound);




void advance_actor_attack_sequence(void *action_state, ObjectPosition *motion, void *animation, ActorRecord *actor);
void advance_effect_fade_and_remove(void *effect, ObjectPosition *motion, SpriteFrameState *primitive);

struct PointRecord;
struct ObjectPosition;
s32 draw_ball_effect_points(struct PointRecord *, struct ObjectPosition *);

/* Callback entry points. */
s32 process_linked_states_mode_zero(void *initial_state, void *context, void *data);
void jitter_effect_position_and_fade(void *effect, void *position, void *sprite);

#endif
