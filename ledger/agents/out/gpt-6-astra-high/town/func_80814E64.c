#include "common.h"

typedef struct {
    s32 position[3];
    s32 velocity[3];
} Movement;

typedef struct {
    u8 pad[0x14];
    u16 flags;
} Object;

extern void func_8003EA54(Object *arg0);
extern s32 D_80084D5C;

/* Advance position by velocity, update the object, and propagate its status flags. */
void func_80814E64(u16 *state, Movement *movement, Object *object) {
    s32 global_flags;

    movement->position[0] += movement->velocity[0];
    movement->position[1] += movement->velocity[1];
    movement->position[2] += movement->velocity[2];
    func_8003EA54(object);
    if (object->flags & 0x6000) {
        state[-1] |= 0x8000;
        do {
            global_flags = D_80084D5C;
        } while (0);
        global_flags |= 0x8000;
        D_80084D5C = global_flags;
    }
}
