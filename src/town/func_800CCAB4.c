#include "common.h"

typedef struct {
    u8 pad[0x6C];
    s16 timer;
} Object;

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
} Position;

typedef struct {
    u8 pad[8];
    Position *target;
} TownState;

typedef struct {
    u8 pad[0xA4];
    s16 transition;
} GameState;

extern GameState D_80083160;
extern TownState D_80083498;

extern void func_800CA774(Object *, Position *, void *, GameState *);
extern void SD_Call(s32);

/* Move halfway toward the target each tick and finish the transition when the timer expires. */
void func_800CA214(Object *object, Position *position, void *context)
{
    s16 ticks_left;
    GameState *game = &D_80083160;

    if (object->timer == 8) {
        game->transition = 0x10;
    }

    ticks_left = (u16)object->timer - 1;
    object->timer = ticks_left;
    if (ticks_left <= 0) {
        func_800CA774(object, position, context, game);
        SD_Call(0x605);
        return;
    }

    position->x += (-position->x + D_80083498.target->x) / 2;
    position->y += (-position->y + D_80083498.target->y) / 2;
    position->z += (-position->z + D_80083498.target->z) / 2;
}
