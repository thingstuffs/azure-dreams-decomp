#ifndef TOWN_MAP_ANIMATION_H
#define TOWN_MAP_ANIMATION_H

#include "common.h"
#include "shared/entity.h"
#include "shared/dungeon_delay_views.h"

typedef union TownMapAnimHalf { s16 s; u16 u; } TownMapAnimHalf;

typedef struct BuildingSelectionHandlerBody {
    /* 0x00 */ TownMapAnimHalf animation_tick;
    /* 0x02 */ s16 selection_kind;
} BuildingSelectionHandlerBody;

/* The randomized spawner seeds the three anchor halves at +0C and the
 * integer halves of the embedded motion at +1C. The animation callback
 * updates both representations before spawning the impact sprite. */
typedef struct TownMapEffectMotion {
    Fixed1616 x, y, z;
    Fixed1616 velocity_x, velocity_y, velocity_z;
} TownMapEffectMotion;

typedef union TownMapFallingMotion {
    TownMapEffectMotion fixed;
    struct {
        u16 x_fraction;
        u16 x_integer;
        u16 y_fraction;
        u16 y_integer;
        u16 z_fraction;
        u16 z_integer;
        u16 velocity_x_fraction;
        u16 velocity_x_integer;
        u16 velocity_y_fraction;
        u16 velocity_y_integer;
        u16 velocity_z_fraction;
        u16 velocity_z_integer;
    } halves;
} TownMapFallingMotion;

typedef struct TownMapFallingObject {
    u8 pad_00[0xC];
    TownMapAnimHalf unk_0C;
    s16 unk_0E;
    TownMapAnimHalf unk_10;
    u8 pad_12[0xA];
    TownMapFallingMotion motion;
    u8 pad_34[0x14];
    TownMapAnimHalf timer;
    u8 pad_4A[2];
    TownMapAnimHalf state;
} TownMapFallingObject;

typedef struct TownMapSpawnState {
    u8 pad_00[8];
    s16 base_y;
    s16 span_y;
    TownMapAnimHalf state;
    u16 count;
} TownMapSpawnState;

/* Body of the spawner that creates short-lived radial objects. */
typedef struct ShortLivedSpawnerObject {
    u8 pad_00[0x48];
    u16 timer;
    s16 count;
} ShortLivedSpawnerObject;

/* initialize_object_header_and_state installs the phase callback and
 * clears these fields; completion clears the linked activity byte. */
typedef struct TownMapPhaseObject {
    u8 pad_00[0x66];
    s16 unk_66;
    TownMapAnimHalf phase;
    u8 pad_6A[2];
    TownMapAnimHalf ticks;
    u8 pad_6E[0x29];
    s8 radius_bias;
    s8 *activity;
} TownMapPhaseObject;

struct SignedPositionView;
struct SpriteFrameState;

/* Node update callback installed by spawn_burst_particles_around_origin. */
void update_effect_motion_size_and_brightness(void *effect_fields, struct SignedPositionView *position, struct SpriteFrameState *sprite);

void advance_object_animation_and_effect(TownMapFallingObject *object);
void spawn_randomized_timed_objects(TownMapSpawnState *source);
void update_four_phase_animation(TownMapPhaseObject *entity, void *context);

/* Callback entry points. */
void advance_building_animation_frame(BuildingSelectionHandlerBody *state);
void advance_building_texture_frame(BuildingSelectionHandlerBody *state);

void copy_low_halfword_coordinates(u16 *destination, const u16 *source);

#endif
