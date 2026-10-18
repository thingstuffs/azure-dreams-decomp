#include "common.h"
#include "shared/entity_objects.h"

typedef struct MotionVector {
    s32 x;
    s32 y;
    s32 z;
    s32 step_x;
    s32 step_y;
    s32 step_z;
} MotionVector;

typedef struct TownActor {
    u8 pad_00[0x6C];
    u16 countdown;
} TownActor;

extern s32 D_800D0428;

extern void add_motion_deltas_to_position(MotionVector *motion);
extern s32 process_the_item_index_available_report_success(TownActor *actor, s32 context,
                         MotionVector *motion, s32 extra, s32 *work);
extern void select_object_value_by_height_band(TownActor *actor, s32 context,
                          MotionVector *motion, s32 extra);

/* Move toward the target and check for completion when the countdown expires. */
void move_toward_target_check_completion_countdown_expires(TownActor *actor, s32 context,
                   MotionVector *motion, s32 extra)
{
    s32 work[5];
    u32 shifted_z;
    u32 delta_y;
    u16 countdown;

    motion->step_x = (s32)((u32)D_80083780.x.v - (u32)motion->x) / 2;
    delta_y = (u32)D_80083780.y.v - (u32)motion->y;
    motion->step_y = (s32)delta_y / 2;
    shifted_z = (u32)motion->z + 0x200000U;
    motion->step_z = (s32)((u32)D_80083780.z.v - shifted_z) / 2;
    add_motion_deltas_to_position(motion);

    countdown = actor->countdown - 1;
    actor->countdown = countdown;
    if (((s32)((u32)countdown << 16) <= 0) &&
        (process_the_item_index_available_report_success(actor, context, motion, extra, work) == 0)) {
        motion->z = (s32)((u32)D_80083780.z.v + (u32)D_800D0428);
        select_object_value_by_height_band(actor, context, motion, extra);
    }
}
