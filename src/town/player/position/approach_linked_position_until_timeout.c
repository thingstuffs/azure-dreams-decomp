#include "common.h"
#include "shared/vector.h"
#include "town.h"
#include "town/player/position.h"


typedef struct PositionLink {
    s8 pad0[8];
    IntVector3 *position;
} PositionLink;

typedef struct TownState {
    u8 pad0[0x10];
    PositionLink *link;
} TownState;

typedef struct TownObject {
    u8 pad0[0xA];
    s16 timer;
} TownObject;

extern TownState town_actor_control;

/*
 * Moves each coordinate halfway toward the linked actor position and starts
 * init_linked_position_action when the countdown becomes negative.
 */
void approach_linked_position_until_timeout(TownObject *object, IntVector3 *position, void *context)
{
    position->x = (town_actor_control.link->position->x + position->x) / 2;
    position->y = (town_actor_control.link->position->y + position->y) / 2;
    position->z = (town_actor_control.link->position->z + position->z) / 2;

    if (--object->timer < 0) {
        init_linked_position_action(object, position, context);
    }
}
