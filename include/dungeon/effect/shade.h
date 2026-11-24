#ifndef DUNGEON_EFFECT_SHADE_H
#define DUNGEON_EFFECT_SHADE_H
struct FadeEffect;
#include "shared/dungeon_effect_source.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
struct Obj;
void apply_random_value_gain(ActorRecord *target, int amount_param, ActorRecord *record);
void apply_conditional_target_effect(ActorRecord *target, int packed_value, void *record);
struct Owner;
void create_owner_color_sprite(struct Owner *owner, unsigned int color);


void advance_damped_effect_motion(void *effect, ObjectPosition *motion, SpriteFrameState *color);
void *create_motion_copy_sprite(void *node_value, ObjectPosition *initial_data);

void *create_radial_effect_from_source(void *owner_body, void *source, int unused, int object_value);

/* Callback entry points. */
int build_sorted_effect_quads(void *quad_entry);
void advance_damped_effect_and_expire(struct FadeEffect *effect, int *motion);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
short check_forward_collision_and_height(ObjectPosition *position, ActorRecord *orientation);

#include "shared/object_node.h"
void spawn_randomized_directional_effect(ObjectNodeHeader *source, short angle, int effect_value, int unused_particle_value);

#include "records/Rec_func_800247B8_arg0.h"
void create_attached_effect(Rec_func_800247B8_arg0 *owner, void *unused_motion, void *unused_sprite);

void create_colored_effect_with_sound(ObjectNodeHeader *source, s32 color, unsigned short sound_id);

#include "records/Rec_func_800D4BD4_arg1.h"
void init_fading_particle_from_emitter(ObjectNodeHeader *object, Rec_func_800D4BD4_arg1 *source, ObjectPosition *position, s32 unused_spawn_context);
void emit_randomized_relative_particles(Rec_func_800D4BD4_arg1 *emitter, ObjectPosition *position, s32 spawn_context);
void create_colored_effect_with_event(ObjectNodeHeader *source, s32 color, unsigned short event_id);

s32 draw_linked_depth_sliced_quads(void *payload, struct ObjectPosition *position, struct SpriteFrameState *render_state);

void *create_effect_object_groups(s16 x, s16 y, s16 z);
s32 draw_adjacent_row_quads(void);
void project_depth_sliced_quads(void *geometry, ObjectPosition *position, SpriteFrameState *render_state, s16 depth_bias);

void finish_actor_effect_action(ActorRecord *action_state, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *actor);

/* The source object a colored effect follows. */
typedef struct ColorEffectSource {
    u8 pad_00[8];
    MovingPosition *position;
} ColorEffectSource;

/* The colored effect object; update_callback takes the object node header's callback slot type. */
typedef struct SourceColorEffect {
    u8 pad_00[8];
    MovingPosition *position;
    SpriteFrameState *render;
    void *update_callback;
    u8 pad_14[0x18];
    u32 color;
    u8 pad_30[0xE];
    u16 lifetime;
    u8 pad_40[4];
    ColorEffectSource *source;
} SourceColorEffect;
void create_parent_particle_color_effect(struct ColorEffectSource *source, u32 color);
void create_periodic_source_color_effect(struct ColorEffectSource *source, u32 color);
void create_alternating_tick_color_effect(struct ColorEffectSource *source, u32 color);

#endif
