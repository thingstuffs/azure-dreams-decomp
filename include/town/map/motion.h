#ifndef TOWN_MAP_MOTION_H
#define TOWN_MAP_MOTION_H
/* Prototypes of the functions defined in src/town/map/motion/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"
#include "town/scene/list_setup.h"

struct SpriteFrameState;
struct TownCourseActor;

typedef struct FadingEffectMotionObject {
    u8 pad_00[0x2];
    union {
        s16 launch_speed;
        u16 remaining_ticks;
    } timer;
    s32 velocity_z_acceleration;
} FadingEffectMotionObject;

/* The initializer registers this sprite node and installs its idle and walk states. */
typedef struct TownWanderBody {
    TownSceneListNode scene;
    u8 pad_18[0x30];
    const u8 *interaction_script;
    u8 pad_4C[4];
    s32 unk_50;
    u8 pad_54[0x14];
    s16 state;
    u8 pad_6A[2];
    s16 ticks;
    u8 pad_6E[0x32];
    s16 tile_offset_y;
    s16 tile_offset_x;
    s16 previous_state;
    s16 direction;
    u8 pad_A8[4];
    s32 action_flags;
} TownWanderBody;

/* init_random_wander_object.c */
void init_random_wander_object(void *object_data, ObjectPosition *motion, struct SpriteFrameState *anim);

/* update_effect_motion_and_fade.c */
void update_effect_motion_and_fade(void *effect, ObjectPosition *motion_data, SpriteFrameState *display_data);

/* update_effect_motion_size_and_brightness.c */
void update_effect_motion_size_and_brightness(void *effect_fields, ObjectPosition *position, SpriteFrameState *sprite);

/* update_fading_effect_motion.c */
void update_fading_effect_motion(FadingEffectMotionObject *effect, ObjectPosition *motion, SpriteFrameState *primitive);

/* update_player_minigame_motion.c */
void update_player_minigame_motion(struct TownCourseActor *actor, ObjectPosition *motion, SpriteFrameState *sprite);

#endif
