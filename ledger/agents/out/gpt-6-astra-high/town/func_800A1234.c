#include "common.h"

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

extern s32 D_80083780[];
extern s32 D_800D0428;

extern void func_8009539C(MotionVector *motion);
extern s32 func_8009EB9C(TownActor *actor, s32 context,
                         MotionVector *motion, s32 extra, s32 *work);
extern void func_8009BFD8(TownActor *actor, s32 context,
                          MotionVector *motion, s32 extra);

/* Move toward the target and check for completion when the countdown expires. */
void func_8009E994(TownActor *actor, s32 context,
                   MotionVector *motion, s32 extra)
{
    s32 work[5];
    s32 *target = D_80083780;
    u32 shifted_z;
    u32 delta_y;
    u16 countdown;

    motion->step_x = (s32)((u32)D_80083780[0] - (u32)motion->x) / 2;
    delta_y = (u32)target[1] - (u32)motion->y;
    motion->step_y = (s32)delta_y / 2;
    shifted_z = (u32)motion->z + 0x200000U;
    motion->step_z = (s32)((u32)target[2] - shifted_z) / 2;
    func_8009539C(motion);

    countdown = actor->countdown - 1;
    actor->countdown = countdown;
    if (((s32)((u32)countdown << 16) <= 0) &&
        (func_8009EB9C(actor, context, motion, extra, work) == 0)) {
        motion->z = (s32)((u32)target[2] + (u32)D_800D0428);
        func_8009BFD8(actor, context, motion, extra);
    }
}
