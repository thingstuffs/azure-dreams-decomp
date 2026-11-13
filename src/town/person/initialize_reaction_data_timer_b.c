#include "common.h"
#include "town/person.h"
typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
} Position;
typedef struct {
    u8 pad[0x6C];
    s16 timer;
} Object;
void move_reaction_toward_target(Object *object, Position *position, void *context);

/* Set the object's data pointer and state to 13. */
void start_reaction_move_toward_target(TownObjectRecord *object) {
    object->handler = &move_reaction_toward_target;
    object->timer = 0xD;
}
