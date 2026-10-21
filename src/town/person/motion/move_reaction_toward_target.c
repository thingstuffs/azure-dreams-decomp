#include "common.h"
#include "shared/game_work.h"

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

extern void initialize_reaction_data_and_timer_10_b(Object *, Position *, void *, GameState *);
extern void SD_Call(s32);

/* Move halfway toward the target each tick and finish the transition when the timer expires. */
void move_reaction_toward_target(Object *object, Position *position, void *context)
{
    s16 ticks_left;
    GameWork *game = &g_game_work;

    if (object->timer == 8) {
        game->view.unk_08C = 0x10;
    }

    ticks_left = (u16)object->timer - 1;
    object->timer = ticks_left;
    if (ticks_left <= 0) {
        initialize_reaction_data_and_timer_10_b(object, position, context, game);
        SD_Call(0x605);
        return;
    }

    position->x += (-position->x + scene_object_list_anchor.target->x) / 2;
    position->y += (-position->y + scene_object_list_anchor.target->y) / 2;
    position->z += (-position->z + scene_object_list_anchor.target->z) / 2;
}
