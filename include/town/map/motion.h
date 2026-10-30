#ifndef TOWN_MAP_MOTION_H
#define TOWN_MAP_MOTION_H
/* Prototypes of the functions defined in src/town/map/motion/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "shared/sprite_frame_state.h"

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

/* initialize_object_motion_and_animation.c */
void initialize_object_motion_and_animation(void *object_data, void *motion, struct SpriteFrameState *anim);

/* update_effect_motion_and_fade.c */
void update_effect_motion_and_fade(void *effect, void *motion_data, void *display_data);

/* update_effect_motion_size_and_brightness.c */
void update_effect_motion_size_and_brightness(void *effect_fields, SignedPositionView *position, SpriteFrameState *sprite);

/* update_fading_effect_motion.c */
void update_fading_effect_motion(FadingEffectMotionObject *effect, ObjectPosition *motion, SpriteFrameState *primitive);

/* update_player_minigame_motion.c */
void update_player_minigame_motion(struct TownCourseActor *actor, ObjectPosition *motion, SpriteFrameState *sprite);

#endif
