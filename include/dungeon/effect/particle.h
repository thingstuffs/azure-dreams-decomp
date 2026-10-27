#ifndef DUNGEON_EFFECT_PARTICLE_H
#define DUNGEON_EFFECT_PARTICLE_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
struct S_81832FE8_0;
void fade_timed_quad_vertices(void *fade_data);
void try_apply_attached_actor_status(struct S_81832FE8_0 *owner);


void advance_centered_fading_effect(void *effect, ObjectPosition *position, void *color);
void advance_projectile_burst_and_impact(void *effect, ObjectPosition *motion, SpriteFrameState *sprite);
void draw_gouraud_textured_ribbon_quad(void *quad, ObjectPosition *position, void *render_state, s16 depth_bias);
void emit_parent_relative_particles(void *emitter, ObjectPosition *position, s32 spawn_context);
void spawn_scattered_emitter_particles(void *emitter, ObjectPosition *position, s32 spawn_context);
void update_converging_fading_particle(void *effect, ObjectPosition *position);
void update_spark_emitter_effect(void *effect, ObjectPosition *position);
void update_timed_effect_animation(void *effect, ObjectPosition *motion, SpriteFrameState *visual);

struct DirectionalEffectWork;
void update_directional_actor_effect(struct DirectionalEffectWork *effect, ObjectPosition *motion, void *context);

void create_owner_linked_mirrored_sprite(void *effect, ObjectPosition *source_position, SpriteFrameState *source_sprite);

/* Callback entry points. */
void expire_ribbon_segment(void *record_data);
void tick_rotating_rect_effect(void *effect, s32 unused, void *phase_state);
void update_color_cycling_pulse(void *state_data, void *unused, void *color);
void update_reverse_rotating_clipped_sprite(void *effect, s32 unused, void *rotation);
void update_staged_particle_emitter(void *effect_data);

#endif
