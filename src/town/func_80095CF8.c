#include "common.h"
#include "shared/types3a_types.h"


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

extern TownState D_800CFCB4;
extern void func_80094834(TownObject *, IntVector3 *, void *);

/* Move halfway toward the linked position and call func_80094834 when the timer expires. */
void approach_linked_position_until_timeout(TownObject *object, IntVector3 *position, void *context)
{
    position->x = (D_800CFCB4.link->position->x + position->x) / 2;
    position->y = (D_800CFCB4.link->position->y + position->y) / 2;
    position->z = (D_800CFCB4.link->position->z + position->z) / 2;

    if (--object->timer < 0) {
        func_80094834(object, position, context);
    }
}
