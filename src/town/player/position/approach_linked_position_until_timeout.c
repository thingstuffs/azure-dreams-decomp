#include "common.h"
#include "shared/vector.h"


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
extern void init_linked_position_action(TownObject *, IntVector3 *, void *);

/* Move halfway toward the linked position and call func_80094834 when the timer expires. */
void approach_linked_position_until_timeout(TownObject *object, IntVector3 *position, void *context)
{
    position->x = (town_actor_control.link->position->x + position->x) / 2;
    position->y = (town_actor_control.link->position->y + position->y) / 2;
    position->z = (town_actor_control.link->position->z + position->z) / 2;

    if (--object->timer < 0) {
        init_linked_position_action(object, position, context);
    }
}
