#ifndef DUNGEON_EFFECT_SHADE_H
#define DUNGEON_EFFECT_SHADE_H
struct FadeEffect;
#include "shared/dungeon_effect_source.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
struct Obj;
void apply_random_value_gain(ActorRecord *target, int amount_param, ActorRecord *record);
void apply_conditional_target_effect(ActorRecord *target, int packed_value, void *record);
struct Owner;
void create_owner_color_sprite(struct Owner *owner, unsigned int color);


void advance_damped_effect_motion(void *effect, ObjectPosition *motion, SpriteFrameState *color);

void *create_radial_effect_from_source(void *owner_body, void *source, int unused, int object_value);

/* Callback entry points. */
int build_sorted_effect_quads(void *quad_entry);
void advance_damped_effect_and_expire(struct FadeEffect *effect, int *motion);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
short check_forward_collision_and_height(EntityRec *position, ActorRecord *orientation);

#include "shared/object_node.h"
void spawn_randomized_directional_effect(ObjectNodeHeader *source, short angle, int effect_value, int unused_particle_value);

#include "records/Rec_func_800247B8_arg0.h"
void create_attached_effect(Rec_func_800247B8_arg0 *owner, void *unused_motion, void *unused_sprite);

void create_colored_effect_with_sound(void *source, s32 color, unsigned short sound_id);

#include "records/Rec_func_800D4BD4_arg1.h"
void initialize_effect_object_state(ObjectNodeHeader *object, Rec_func_800D4BD4_arg1 *source, ObjectPosition *position, s32 unused_spawn_context);
void create_colored_effect_with_event(ObjectNodeHeader *source, s32 color, unsigned short event_id);

s32 draw_linked_depth_sliced_quads(void *payload, struct ObjectPosition *position, struct SpriteFrameState *render_state);

void *create_effect_object_groups(s16 x, s16 y, s16 z);
s32 draw_adjacent_row_quads(void);
void project_depth_sliced_quads(void *geometry, ObjectPosition *position, SpriteFrameState *render_state, s16 depth_bias);

void reset_action_and_decrement_actor_count(ActorRecord *action_state, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *actor);

#endif
