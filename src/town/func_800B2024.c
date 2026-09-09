#include "common.h"

typedef struct {
    u8 pad00[0x10];
    s32 current;
    s32 limit;
} State;

typedef struct {
    u8 pad00[0x98];
    void **primary;
    void **secondary;
} Outputs;

typedef struct {
    State * volatile state;
    u8 pad04[0x10];
    volatile u32 flags;
    u8 pad18[0x90];
    Outputs *outputs;
} Object;

extern u8 D_800786DC[];
extern u8 D_800786E8[];

/* Updates both outputs and their flags from the current state and limit. */
void func_800AF784(Object *obj)
{
    register State *state;
    s32 clear_mask;

    if (obj->state->current > 0) {
        u32 flags;

        *obj->outputs->primary = D_800786DC;
        flags = obj->flags;
        flags &= ~2;
        obj->flags = flags;
    } else {
        *obj->outputs->primary = 0;
        obj->flags |= 2;
    }
    state = obj->state;
    if (state->current < state->limit) {
        do {
            clear_mask = -2;
        } while (0);
        obj->flags &= clear_mask;
        *obj->outputs->secondary = D_800786E8;
        return;
    }

    *obj->outputs->secondary = 0;
    obj->flags |= 1;
}
