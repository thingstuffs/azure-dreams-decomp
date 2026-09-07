#include "common.h"

typedef struct {
    u8 pad_00[0x50];
    void *state;
    u8 pad_54[0x18];
    u16 timer;
    u8 pad_6E[0x22];
    s16 value;
} State;

extern u8 D_800AB55C[];
extern u8 D_800AB708[];

void func_800AB50C(State *arg0) {
    u16 timer;

    if (arg0->value < 100) {
        arg0->state = D_800AB708;
    }
    timer = arg0->timer - 1;
    arg0->timer = timer;
    if ((s16) timer < 0) {
        arg0->state = D_800AB55C;
        arg0->timer = 10;
    }
}
