#ifndef TOWN_MINIGAME_OBJECT_H
#define TOWN_MINIGAME_OBJECT_H
/* Prototypes of the functions defined in src/town/minigame/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/dungeon_moving_views.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct GymScoreObject;
struct IndicatorChild;
struct S_800BF72C_1;
struct State8081A3D8;

/* Body for the minigame target routine's phase, countdown, and setup value. */
typedef struct ObjectStatePositionObject {
    /* 0x00 */ u8 pad_00[0x48];
    /* 0x48 */ s32 setup_value;
    /* 0x4C */ u8 pad_4C[0x1C];
    /* 0x68 */ s16 phase;
    /* 0x6A */ u8 pad_6A[2];
    /* 0x6C */ s16 countdown;
} ObjectStatePositionObject;

/* Body that tracks a minigame transition's controller, linked object, and mode. */
typedef struct MinigameTransitionObject {
    /* 0x00 */ s16 state;
    /* 0x02 */ u8 pad_02[2];
    /* 0x04 */ void *object;
    /* 0x08 */ u8 pad_08[0x4C];
    /* 0x54 */ union { s16 s; u16 u; } mode;
} MinigameTransitionObject;

/* Body for the minigame text value and its initialized display fields. */
typedef struct MinigameTextValueObject {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ char *text;
    /* 0x08 */ u8 pad_08[8];
    /* 0x10 */ s32 color;
    /* 0x14 */ s16 x;
    /* 0x16 */ s16 y;
    /* 0x18 */ s16 scale_y;
    /* 0x1A */ s16 scale_x;
} MinigameTextValueObject;

/* Body of the object advanced through bounded horizontal and vertical phases. */
typedef struct BoundedMovementObject {
    /* 0x00 */ u8 pad_00[0x68];
    /* 0x68 */ s16 movement_state;
    /* 0x6A */ u8 pad_6A[0x36];
    /* 0xA0 */ void *linked_object;
} BoundedMovementObject;

/* Body for timed text displays with overlapping coordinate and timer views. */
typedef struct SpawnDisplayObject {
    /* 0x00 */ u8 pad_00[2];
    /* 0x02 */ s16 timer;
    /* 0x04 */ union {
        struct { void *v; } at00;
        struct { u8 pad[2]; s16 v; } at02;
    } unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[2]; s16 v; } at02;
    } unk_0C;
    /* 0x10 */ union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[2]; s16 v; } at02;
    } unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ union { s16 s; u16 u; } unk_16;
    /* 0x18 */ u8 pad_18[2];
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} SpawnDisplayObject;

/* Body whose linked-value pointer is retired after the gym sprite updates. */
typedef struct GymSpriteObject {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ s32 field_04;
    /* 0x08 */ void *field_08;
    /* 0x0C */ union { void *object; s16 *linked_value; } link;
    /* 0x10 */ s32 field_10;
    /* 0x14 */ s16 field_14;
    /* 0x16 */ s16 field_16;
    /* 0x18 */ s16 field_18;
    /* 0x1A */ s16 field_1A;
    /* 0x1C */ u8 pad_1C[0x34];
    /* 0x50 */ s16 field_50;
    /* 0x52 */ s16 field_52;
    /* 0x54 */ s16 field_54;
} GymSpriteObject;

/* advance_object_bounded_movement_phases.c */
void advance_object_bounded_movement_phases(BoundedMovementObject *object, struct S_800BF72C_1 *position);

/* advance_object_spawning_displays_high.c */
void advance_object_spawning_displays_high(struct State8081A3D8 *controller);

/* apply_minigame_object_tint.c */
void apply_minigame_object_tint(struct IndicatorChild *state, MovingPosition *selected_values, SpriteFrameState *render_state);

/* create_gym_mesh_object.c */
void create_gym_mesh_object(void *source_words, s32 data_value_08, s32 object_value_10, s32 object_value_20);

/* create_scene_object_with_byte_payload.c */
void create_scene_object_with_48_byte_payload(s32 init_value, void *init_data);

/* create_scene_object_with_record_payload.c */
void create_scene_object_with_record_payload(void *object_value, void *record);

/* decrement_object_counter.c */
void decrement_object_counter(void *entry);

/* fade_linked_object_color.c */
void fade_linked_object_color(void *fade);

/* retire_scene_node_when_linked_value_clears.c */
void retire_scene_node_when_linked_value_clears(GymSpriteObject *record);

/* update_gym_score_object.c */
void update_gym_score_object(struct GymScoreObject *obj, ObjectPosition *motion);

/* update_object_movement_proximity_reactions.c */
void update_object_movement_proximity_reactions(void *state_data, void *position_data, void *sprite_data);

#endif
