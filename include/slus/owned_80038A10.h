#ifndef SLUS_OWNED_80038A10_H
#define SLUS_OWNED_80038A10_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/game_work.h"

#include "common.h"

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

extern Func80038A10State *D_80081448;
struct RuntimeContext;
extern s32 func_80038AB8(struct RuntimeContext *, u8 *);
extern void update_message_window(Func80038A10State *);
extern void func_80038A10(Func80038A10State *);

/* Processes the current state until processing stops or its handler changes. */

void update_message_window(Func80038A10State *input_state);
void func_80038A10(Func80038A10State *input_state);

#endif
