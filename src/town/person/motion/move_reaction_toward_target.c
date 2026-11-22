#include "common.h"
#include "shared/game_work.h"
#include "slus.h"
#include "town/person.h"

#include "shared/object_node.h"
#include "town/person/motion.h"

/* Move halfway toward the target each tick and finish the transition when the timer expires. */
void move_reaction_toward_target(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite)
{
    s16 ticks_left;
    GameWork *game = &g_game_work;

    if ((s16)object->timer == 8) {
        game->view.unk_08C = 0x10;
    }

    ticks_left = object->timer - 1;
    object->timer = ticks_left;
    if (ticks_left <= 0) {
        start_reaction_ease_to_target(object, position, sprite, game);
        SD_Call(0x605);
        return;
    }

    position->x.w.i += (-position->x.w.i + scene_object_list_anchor.position->x.w.i) / 2;
    position->y.w.i += (-position->y.w.i + scene_object_list_anchor.position->y.w.i) / 2;
    position->z.w.i += (-position->z.w.i + scene_object_list_anchor.position->z.w.i) / 2;
}
