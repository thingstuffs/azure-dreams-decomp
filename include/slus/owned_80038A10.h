#ifndef SLUS_OWNED_80038A10_H
#define SLUS_OWNED_80038A10_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/game_work.h"


typedef struct Func80038A10State Func80038A10State;

struct Func80038A10State {
    u8 pad0[0x10];
    void (*func10)(Func80038A10State *);
    u8 pad14[0x1A];
    u8 field2E;
    u8 pad2F[0x51];
    void *field80;
    u8 pad84[3];
    s8 field87;
};

extern Func80038A10State *current_message_window_state;
struct RuntimeContext;
extern void func_80038A10(Func80038A10State *);

/* Processes the current state until processing stops or its handler changes. */

void func_80038A10(Func80038A10State *input_state);

#endif
