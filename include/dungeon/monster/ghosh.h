#ifndef DUNGEON_MONSTER_GHOSH_H
#define DUNGEON_MONSTER_GHOSH_H

#include "common.h"
#include "shared/object_node.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"

/* Twelve copied sprite-source bytes; aggregate alignment remains one byte. */
typedef struct GhoshSpriteTemplate {
    u8 bytes[12];
} GhoshSpriteTemplate;

extern GhoshSpriteTemplate ghosh_sprite_payload_template;

/* Byte-command streams and their halfword repeat counters. */
extern u8 *ghosh_script_cursor;
extern s16 ghosh_script_repeat_count;
extern u8 *ghosh_command_stream;
extern s16 ghosh_command_ticks;

typedef struct GhoshDirectionOffset {
    s16 x;
    s16 y;
} GhoshDirectionOffset;

extern GhoshDirectionOffset ghosh_effect_direction_offsets[8];

extern ObjectNodeHeader *ghosh_scripted_actor;

extern ObjectNodeHeader *D_80174CDC;

extern ObjectNodeHeader *ghosh_actor_node;

extern ObjectNodeHeader *D_80174CC8;

extern ObjectNodeHeader *ghosh_boss_node;

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 ghosh_direction_frames[];
extern u8 ghosh_ready_action_frames[];

void create_boss_child_effect(void *parent_data, MovingPosition *source_pos, void *sprite_template);
void create_boss_directional_effect(void *source, s16 angle, s32 initial_value, s32 unused, s16 spread_mode);
void release_secondary_overlay_object(void);


void update_boss_actor_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);



void update_actor_animation_movement_and_terrain(void *entity, ObjectPosition *motion, void *sprite);
void update_boss_actor_movement(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);

typedef union GhoshFadeColor {
    s32 word;
    struct { s8 r, g, b, pad; } rgb;
} GhoshFadeColor;

typedef struct GhoshTrailFade {
    u8 r, g, b, pad03;
    GhoshFadeColor scaled;
    s32 color;
    u8 pad0C[0x26];
    union { s16 s; u16 u; } steps;
    s16 divisor;
} GhoshTrailFade;

void advance_ghosh_trail_fade(GhoshTrailFade *fade, ObjectPosition *position);

/* Callback entry points. */
void advance_three_state_bytes(u16 *words);
void animate_timed_fade_effect(void *effect);
void apply_boss_direction_table_state(void *record_data);
void update_object_motion_and_landing(void *motion, void *position, void *object);

/* begin_ghosh_front_attack.c and its imports. */
s32 begin_ghosh_front_attack(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
u32 check_entity_interaction_compatibility(void *entity, void *other_entity);
s32 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record); /* callers here use the full return register */
s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
void prepare_directional_attack(ActorRecord *actor, SpriteFrameState *sprite, s16 facing, s32 mode, s32 extra);
void set_boss_effect_data_pointer(ActorRecord *object, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *flag_owner);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct S_801720D0_0;
void advance_boss_actor_movement_state(void *move_state, void *unused, void *position_in, void *actor_in);
void allocate_type_12_object(void);
void spawn_rising_trail_emitter(void);
void update_rising_trail_emitter(void *record_data, struct S_801720D0_0 *state);

#endif
