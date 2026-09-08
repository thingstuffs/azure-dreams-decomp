#include "common.h"

typedef struct {
    u8 pad_00[0x50];
    void *state;
    u8 pad_54[0x18];
    u16 timer;
    u8 pad_6E[4];
    u16 unk72;
    u8 pad_74[0x1C];
    s16 value;
} State;

extern u8 D_800AB50C[];
extern u8 D_800AB708[];

void func_800AB4A8(State *arg0) {
    u16 timer;

    if (arg0->value < 100) {
        arg0->state = D_800AB708;
    }
    timer = arg0->timer - 1;
    arg0->timer = timer;
    if ((s16) timer < 0) {
        arg0->state = D_800AB50C;
        arg0->timer = 20;
        return;
    }
    arg0->unk72 += 0x200;
}
