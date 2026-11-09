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
void initialize_reaction_data_and_timer_13(TownObjectRecord *object) {
    object->handler = &move_reaction_toward_target;
    object->timer = 0xD;
}
