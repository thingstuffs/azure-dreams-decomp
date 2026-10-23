#ifndef TOWN_MAP_COURSE_H
#define TOWN_MAP_COURSE_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/minigame_body.h"

typedef union TownCourseHalf { s16 s; u16 u; } TownCourseHalf;

/* fill_eligible_negative_slots and the motion callback share the course;
 * +30 holds four lap times, read signed for the best-time comparison. */
typedef struct TownCourse {
    u8 pad_00[0x2E];
    u16 unk_2E;
    TownCourseHalf lap_times[4];
    s16 best_time;
    u8 pad_3A[2];
    s16 surface_kind;
} TownCourse;

/* Node body installed by initialize_object_rendering_resources. This is a
 * course callback record, separate from the stat-bearing ActorRecord. */
typedef struct TownCourseActor {
    u8 pad_00[8];
    s16 state;
    u8 pad_0A[6];
    TownCourseHalf facing;
    s16 sprite_direction;
    u8 pad_14[4];
    s16 unk_18;
    u8 pad_1A[2];
    u8 *direction_frames;
    u8 pad_20[0x28];
    s32 speed;
    s32 flags;
    MinigameProgressPair16 progress;
    TownCourse *course;
    s32 impulse_x;
    s32 impulse_y;
} TownCourseActor;

void initialize_object_rendering_resources(TownCourseActor *object_data, void *unused, SpriteFrameState *render_data);
void update_player_minigame_motion(TownCourseActor *actor, ObjectPosition *motion, SpriteFrameState *sprite);

#endif
