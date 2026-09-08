#include "common.h"

#include "common.h"

typedef s32 (*Func80038690Handler)(s32, s32, s32, s32);

typedef struct {
    u8 pad_00[0x40];
    Func80038690Handler *handlers;
    u8 pad_44[4];
    s32 arg0;
    s32 arg1;
    s32 arg2;
    s32 arg3;
    u8 pad_58[0x2C];
    s32 callback_result;
} Func80038690Context;

typedef struct {
    u8 pad_00[0x10];
    void (*callback)(void);
    u8 pad_14[0x1E];
    s8 table_index;
    u8 pad_33[1];
    s32 result;
    u8 pad_38[0x48];
    Func80038690Context *context;
} Func80038690State;

extern void func_80038A10(void);

/* Run the selected handler and advance the state callback on a nonzero result. */
void func_80038690(Func80038690State *state) {
    Func80038690Context *context = state->context;
    s32 result;

    result = context->handlers[state->table_index](context->arg0, context->arg1,
                                                  context->arg2, context->arg3);
    context->callback_result = result;
    if (result != 0) {
        state->result = result;
        state->callback = func_80038A10;
    }
}
