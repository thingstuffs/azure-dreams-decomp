#include "common.h"
#include "shared/game_work.h"
#include "slus.h"
#include "town/person.h"

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

extern TownState scene_object_list_anchor;

/* Move halfway toward the target each tick and finish the transition when the timer expires. */
void move_reaction_toward_target(Object *object, ObjectPosition *position, void *context)
{
    s16 ticks_left;
    GameWork *game = &g_game_work;

    if (object->timer == 8) {
        game->view.unk_08C = 0x10;
    }

    ticks_left = (u16)object->timer - 1;
    object->timer = ticks_left;
    if (ticks_left <= 0) {
        start_reaction_ease_to_target(object, position, context, game);
        SD_Call(0x605);
        return;
    }

    position->x.w.i += (-position->x.w.i + scene_object_list_anchor.target->x) / 2;
    position->y.w.i += (-position->y.w.i + scene_object_list_anchor.target->y) / 2;
    position->z.w.i += (-position->z.w.i + scene_object_list_anchor.target->z) / 2;
}
