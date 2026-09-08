#include "common.h"

typedef struct {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
} TownCoordPair;

typedef struct {
    u8 pad0[8];
    TownCoordPair *coords;
} TownCoordOwner;

typedef struct {
    u32 x;
    u32 y;
} TownVec2;

typedef struct {
    u8 pad0[0x6C];
    u16 countdown;
} TownActor;

extern TownCoordOwner *D_8008267C;
extern s32 func_800C4174(TownActor *, TownVec2 *, s32);

/* Moves the position toward the town coordinates plus a vertical offset until the countdown expires. */
void func_800CC8AC(TownActor *actor, TownVec2 *position, s32 completion_arg)
{
    TownCoordPair *coords;
    s32 coord_x;
    s32 base_y;
    s32 coord_y;
    s32 ticks_left;
    u32 target_x;
    u32 target_y;
    u16 countdown;

    coords = D_8008267C->coords;
    coord_x = coords->x;
    base_y = coords->y;
    countdown = actor->countdown - 1;
    actor->countdown = countdown;
    ticks_left = (s16)countdown;
    coord_y = base_y + 0x60;
    target_x = (u32)coord_x << 16;
    coord_x = target_x;
    target_y = (u32)coord_y << 16;
    coord_y = target_y;

    if (ticks_left <= 0) {
        position->x = target_x;
        position->y = target_y;
        func_800C4174(actor, position, completion_arg);
        return;
    }

    position->x +=
        (u32)((s32)(coord_x - position->x) / ticks_left);
    position->y +=
        (u32)((s32)(coord_y - position->y) / (s16)actor->countdown);
}
