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

void func_800CC8AC(TownActor *actor, TownVec2 *position, s32 arg2)
{
    TownCoordPair *coords;
    s32 coord_x;
    s32 raw_y;
    s32 coord_y;
    s32 remaining;
    u32 target_x;
    u32 target_y;
    u16 countdown;

    coords = D_8008267C->coords;
    coord_x = coords->x;
    raw_y = coords->y;
    countdown = actor->countdown - 1;
    actor->countdown = countdown;
    remaining = (s16)countdown;
    coord_y = raw_y + 0x60;
    target_x = (u32)coord_x << 16;
    coord_x = target_x;
    target_y = (u32)coord_y << 16;
    coord_y = target_y;

    if (remaining <= 0) {
        position->x = target_x;
        position->y = target_y;
        func_800C4174(actor, position, arg2);
        return;
    }

    position->x +=
        (u32)((s32)(coord_x - position->x) / remaining);
    position->y +=
        (u32)((s32)(coord_y - position->y) / (s16)actor->countdown);
}
