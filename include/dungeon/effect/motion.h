#ifndef DUNGEON_EFFECT_MOTION_H
#define DUNGEON_EFFECT_MOTION_H
struct B22_81893474_EffectState;
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
struct ColorEffectSource;
struct SpellMotion;
void create_brief_positioned_color_effect(struct ColorEffectSource *source, s32 color);
void * create_orbit_sprite_at_index(struct SpellMotion *origin, s16 index);
s32 draw_counter_rotating_cylinders(struct B22_81893474_EffectState *effect, MovingPosition *center, s32 unused_value);
void spawn_jittered_child_effect( void *source, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void spawn_variant_effect_with_random_motion(s32 pos_x, s32 pos_y, s32 pos_z, u32 variant);
struct Row_81916F10_S_80024710_0;
struct Row_81916F10_S_80024710_2;
void update_orbit_projectile_trail(struct Row_81916F10_S_80024710_0 *object, struct Row_81916F10_S_80024710_2 *position);

/* Body allocated by create_item_drop_effect and advanced until the item is
 * placed at its saved grid position. */
typedef struct ItemDropEffectBody {
    u8 pad_00[0xA2];
    s16 state;
    u16 frames_left;
    u8 pad_A6[0xA];
    s16 grid_x;
    s16 grid_y;
} ItemDropEffectBody;

void animate_item_drop_effect(ItemDropEffectBody *object, ObjectPosition *motion, SpriteFrameState *display);

/* Body allocated with flags 0x201 by the bank timed-visual sequence and its
 * relinks. create_cylindrical_effect decrements +0x48, advances +0x4C and
 * toggles +0x58. The spawner copies the attachment origin to +0x0C..+0x10. */
typedef struct CylindricalEffectWork {
    u8 pad_00[0xC];
    s16 origin_x, origin_y, origin_z;
    u8 pad_12[0x36];
    u16 timer;
    u8 pad_4A[2];
    s16 stage;
    u8 pad_4E[0xA];
    s32 shade;
} CylindricalEffectWork;

/* Effect parameters and countdown used by update_spiral_spawner. */
typedef struct SpiralingEffectObjectBody {
    u8 pad_00[0xC];
    ActorRecord *target;
    u8 pad_10[0x16];
    s16 facing;
    u8 pad_28[0x4];
    s16 frames_left;
    u8 pad_2E[0x2];
    s16 spell_variant;
} SpiralingEffectObjectBody;

/* Set to 1 by running particle/point effects every frame; the effect
 * controller in entry_play_sound_if_enabled clears it and finishes the effect
 * once a whole period passes with it still clear. */
extern s16 particle_effect_active;

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 draw_concentric_effect_layers(struct B22_81893474_EffectState *effect, s32 position, s32 render_param);
s32 draw_static_cylinder_pair(struct B22_81893474_EffectState *effect, s32 position, s32 render_param);
void update_spiral_spawner(void *state);

/* Both flight sprites keep the parent spell in their node body. */
struct OrbitBurstSpell;

typedef struct LinkedCounterSpriteBody {
    u8 pad_00[0xC];
    struct OrbitBurstSpell *owner;
} LinkedCounterSpriteBody;

struct ObjectNodeHeader;
struct ObjectNodeHeader *allocate_effect_at_coordinates(struct OrbitBurstSpell *owner, struct SpellMotion *source_coords);
void advance_delayed_sprite_animation(void *state, void *unused, SpriteFrameState *sprite);
void advance_linked_object_counter(LinkedCounterSpriteBody *entry, ObjectPosition *unused, SpriteFrameState *target);

void select_target_sprite_scale(ActorRecord *record_field, s32 pair_index);

/* Orbit center and angle for the indexed-color sprite. */
typedef struct IndexedColorSpriteBody {
    u16 center_x;
    u16 center_y;
    u8 pad_04[0x4];
    s16 orbit_angle;
} IndexedColorSpriteBody;

/* Target ownership marker written when the homing effect completes. */
typedef struct RadialOffsetSpriteEffectBody {
    u8 pad_00[0x8];
    s16 angle;
} RadialOffsetSpriteEffectBody;

/* Radius, rotation, and countdown for a spiraling effect. */
typedef struct SpiralingBody {
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    u8 pad_0C[0x4];
    s16 center_x;
    s16 center_y;
    u8 pad_14[0x10];
    union { s16 s; u16 u; } state;
    u8 pad_26[0x2];
    union { s16 s; u16 u; } orbit_angle;
    u16 frame_count;
    s16 frames_left;
    u8 pad_2E[0x6];
    s16 radius;
} SpiralingBody;

s32 random_below_limit(s32 limit);

#include "shared/dungeon_effect_views.h"
s32 draw_ball_effect_points(PointRecord *first_point, ObjectPosition *first_position);

void retire_finished_sprite_effect(void *body, ObjectPosition *position, SpriteFrameState *sprite);
void *create_random_rotation_effect_sprite(struct OrbitBurstSpell *owner, struct SpellMotion *position);
void advance_random_rotation_flight_sprite(LinkedCounterSpriteBody *body, ObjectPosition *unused, SpriteFrameState *target);

void *create_effect_sprite_at(struct SpellMotion *source);
void spawn_sprite_at_random_radial_offset(struct SpellMotion *origin);
s32 dispatch_effect_rendering(struct B22_81893474_EffectState *effect, s32 position, s32 render_param);

#endif
