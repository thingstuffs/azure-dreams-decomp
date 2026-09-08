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
extern void func_80053DA8(s32);

void func_800CA214(Object *object, Position *position, void *arg2)
{
    s16 timer;
    GameState *game = &D_80083160;

    if (object->timer == 8) {
        game->transition = 0x10;
    }

    timer = (u16)object->timer - 1;
    object->timer = timer;
    if (timer <= 0) {
        func_800CA774(object, position, arg2, game);
        func_80053DA8(0x605);
        return;
    }

    position->x += (-position->x + D_80083498.target->x) / 2;
    position->y += (-position->y + D_80083498.target->y) / 2;
    position->z += (-position->z + D_80083498.target->z) / 2;
}
