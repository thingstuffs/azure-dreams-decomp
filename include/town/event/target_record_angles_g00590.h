#ifndef TOWN_EVENT_TARGET_RECORD_ANGLES_G00590_H
#define TOWN_EVENT_TARGET_RECORD_ANGLES_G00590_H
/* inferred-strong G00590: target_record_angles_g00590; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC708, CL:town/func_800AC9AC, PD:town/engine:80100D18, PD:town/engine:80100D40, PD:town/engine:80100D42. */

#include "common.h"
#include "town/event/mesh_motion.h"
#include "shared/vector.h"

typedef struct {
    u8 pad0[8];
    s16 field8;
    s16 fieldA;
    u8 padC[4];
    s32 field10;
    s32 field14;
    s32 field18;
} TownRecord;

extern TownRecord D_800D1178;
extern TownRecord D_800D119C;

extern void transform_and_queue_mesh_quads();
extern s32 rsin(s32);
extern s32 rcos(s32);

extern IntVector3 town_motion_offset_position, D_80100D68;
extern PositionRotationPair town_event_motion_pair;

extern u16 town_motion_x_phase, town_motion_y_phase, town_motion_x_step, town_motion_y_step;
extern void draw_random_colored_line(s32, s32);

/* Functions defined in this translation unit. */
void apply_two_records_to_target(s32 target, s32 setup_data);
void update_positions_from_origin(IntVector3 *origin);

#endif
