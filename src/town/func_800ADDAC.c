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

/* Updates the state from the value and countdown, resetting an expired timer to ten. */
void func_800AB50C(State *record) {
    u16 timer;

    if (record->value < 100) {
        record->state = D_800AB708;
    }
    timer = record->timer - 1;
    record->timer = timer;
    if ((s16) timer < 0) {
        record->state = D_800AB55C;
        record->timer = 10;
    }
}
