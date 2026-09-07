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

void func_80814E64(u16 *arg0, Movement *arg1, Object *arg2) {
    s32 value;

    arg1->position[0] += arg1->velocity[0];
    arg1->position[1] += arg1->velocity[1];
    arg1->position[2] += arg1->velocity[2];
    func_8003EA54(arg2);
    if (arg2->flags & 0x6000) {
        arg0[-1] |= 0x8000;
        do {
            value = D_80084D5C;
        } while (0);
        value |= 0x8000;
        D_80084D5C = value;
    }
}
