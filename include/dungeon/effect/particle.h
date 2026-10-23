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

#endif
