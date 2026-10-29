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
struct RibbonLineGeometry;
void draw_ribbon_center_lines(struct RibbonLineGeometry *geometry, ObjectPosition *position, SpriteFrameState *render_data, s32 depth_bias);
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

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/dungeon_effect_views.h"
struct D_800DB420_Obj;
struct D_800DB420_RngOut;
struct S_func_81856800_1;
struct S_func_81856800_2;
struct S_func_818DA800_1;
struct S_func_818DA800_2;
void advance_jittered_effect_modes(struct D_800DB420_Obj *state, struct D_800DB420_RngOut *position, SpriteFrameState *effect);
s32 draw_flagged_particle_points(PointRecord *first_point, ObjectPosition *first_position);
s32 draw_linked_textured_quads(void *first_quad);
void fade_linked_display_sprite(void *effect, void *unused_context, void *effect_params);
void fade_packed_object_color_to_zero(void *object);
void fade_tinted_display_sprite(void *effect, void *unused, void *primitive);
void run_fading_sprite_projectile(struct S_func_81856800_1 *action, struct S_func_81856800_2 *motion_arg);
void run_growing_target_effect(struct S_func_818DA800_1 *effect_state, struct S_func_818DA800_2 *motion);
void spawn_scattered_timed_objects(void *source_owner, void *spawn_params);
void update_animated_textured_ribbon(u8 *effect, void *origin, void *color_in);
void update_flickering_layer_sprite(void *effect_data, void *unused, SpriteFrameState *effect);
void update_landing_particle_fade(u8 *object, u8 *motion, u8 *sprite);
void update_rotating_effect_vertices(void *effect_data);

#endif
