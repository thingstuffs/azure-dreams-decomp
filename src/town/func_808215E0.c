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

void func_80023DE0(Town215E0State *arg0, s32 arg1, Town215E0Actor *arg2) {
    u16 value;

    arg0->timer--;
    switch (arg0->state) {
    case 0:
        if (arg0->inner->field5C == 4) {
            arg0->timer = 10;
            arg0->state++;
        }
        break;

    case 1:
        arg2->field16 += 64;
        if (arg0->timer <= 0) {
            arg0->state++;
        }
        break;

    case 2:
        value = arg2->field16 - 24;
        arg2->field16 = value;
        if (value < 24) {
            arg2->field16 = 0;
            arg0->state = 0;
        }
        break;

    default:
        break;
    }
}
