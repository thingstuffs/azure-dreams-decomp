#ifndef TOWN_MINIGAME_GYM_H
#define TOWN_MINIGAME_GYM_H
#include "common.h"
#include "shared/game_state.h"
#include "shared/entity.h"

extern s16 gym_lane;
extern s16 gym_lane_delay;
extern s16 gym_lane_positions[];

/* Controller body created by initialize_gym_minigame and linked at the
 * first word of every score object. Score updates signal flags 1/2 and
 * read the score signed; the controller initializes it unsigned. */
typedef union GymHalf { s16 s; u16 u; } GymHalf;

typedef struct GymState {
    GymHalf state;
    GymHalf timer;
    u8 pad_04[2];
    u16 flags;
    GymHalf score;
} GymState;

/* The gym initializer links this sprite to its controller and installs the
 * phase callback, which reads the controller's state through the first word. */
typedef struct GymPhaseSpriteBody {
    GymState *controller;
    u8 scene_node; /* address passed to init_scene_node_mode_3 */
    u8 pad_05[0x47];
    s32 *shared_data;
} GymPhaseSpriteBody;

typedef struct GymScoreObject {
    GymState *child;
    u8 pad_04[0x4C];
    s16 state;
    s16 timer;
    s16 target;
} GymScoreObject;

void update_gym_minigame(GymState *state_obj);
void update_gym_score_object(GymScoreObject *obj, ObjectPosition *motion);

#endif
