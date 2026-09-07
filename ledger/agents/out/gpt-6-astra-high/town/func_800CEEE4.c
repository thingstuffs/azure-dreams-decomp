#include "common.h"

typedef struct { s16 pad0; s16 x; s16 pad4; s16 y; } TownTarget;
typedef struct { u8 pad0[8]; TownTarget *target; } TownContext;
typedef struct { u32 x; u32 y; } TownPosition;
typedef struct { u8 pad0[0x6C]; u16 timer; } TownObject;

extern TownContext *D_8008267C;
extern void func_800C4174(TownObject *, TownPosition *, s32);

/* Move toward the offset target position and finish when the timer expires. */
void func_800CC644(TownObject *object, TownPosition *position, s32 finish_arg)
{
    TownTarget *target;
    s32 raw_x;
    s32 raw_y;
    s32 coord_x;
    s32 coord_y;
    s32 frames_left;
    u32 target_x;
    u32 target_y;
    u16 timer;

    target = D_8008267C->target;
    raw_x = target->x;
    raw_y = target->y;
    timer = object->timer - 1;
    object->timer = timer;
    frames_left = (s16)timer;
    coord_x = raw_x + 0x60;
    coord_y = raw_y + 0x20;
    target_x = (u32)coord_x << 16;
    coord_x = target_x;
    target_y = (u32)coord_y << 16;
    coord_y = target_y;

    if (frames_left <= 0) {
        position->x = target_x;
        position->y = target_y;
        func_800C4174(object, position, finish_arg);
        return;
    }

    position->x += (u32)((s32)(coord_x - position->x) / frames_left);
    position->y +=
        (u32)((s32)(coord_y - position->y) / (s16)object->timer);
}
