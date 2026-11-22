#include "common.h"
#include "shared/vector.h"
#include "town.h"
#include "town/player/action_initializers.h"
#include "town/player/position.h"


typedef struct PositionLink {
    s8 pad0[8];
    IntVector3 *position;
} PositionLink;

typedef struct TownState {
    u8 pad0[0x10];
    PositionLink *link;
} TownState;


extern TownState town_actor_control;

/*
 * Moves each coordinate halfway toward the linked actor position and starts
 * init_linked_position_action when the countdown becomes negative.
 */
void approach_linked_position_until_timeout(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *sprite)
{
    position->x.v = (town_actor_control.link->position->x + position->x.v) / 2;
    position->y.v = (town_actor_control.link->position->y + position->y.v) / 2;
    position->z.v = (town_actor_control.link->position->z + position->z.v) / 2;

    if (--object->unk_0A < 0) {
        init_linked_position_action(object, position, sprite);
    }
}
