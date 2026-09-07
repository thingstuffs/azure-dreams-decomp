#include "common.h"

typedef struct Town215E0Inner {
    u8 pad0[0x5C];
    s16 field5C;
} Town215E0Inner;

typedef struct Town215E0State {
    Town215E0Inner *inner;
    s16 state;
    s16 timer;
} Town215E0State;

typedef struct Town215E0Actor {
    u8 pad0[0x16];
    u16 field16;
} Town215E0Actor;

/* Updates a triggered rise-and-decay cycle for the actor's field16. */
void func_80023DE0(Town215E0State *cycle, s32 unused, Town215E0Actor *actor) {
    u16 reduced_value;

    cycle->timer--;
    switch (cycle->state) {
    case 0:
        if (cycle->inner->field5C == 4) {
            cycle->timer = 10;
            cycle->state++;
        }
        break;

    case 1:
        actor->field16 += 64;
        if (cycle->timer <= 0) {
            cycle->state++;
        }
        break;

    case 2:
        reduced_value = actor->field16 - 24;
        actor->field16 = reduced_value;
        if (reduced_value < 24) {
            actor->field16 = 0;
            cycle->state = 0;
        }
        break;

    default:
        break;
    }
}
