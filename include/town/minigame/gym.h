#ifndef TOWN_MINIGAME_GYM_H
#define TOWN_MINIGAME_GYM_H
#include "common.h"
#include "shared/entity.h"

extern s16 gym_lane;
extern s16 gym_lane_delay;
extern s16 gym_lane_positions[];
extern u16 gym_high_score[];

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
