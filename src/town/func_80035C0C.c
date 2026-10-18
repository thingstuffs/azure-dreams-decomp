/* Update alternate menu page bounds. */
#include "common.h"

typedef struct {
    u8 pad00[0x1C];
    s32 current;
    s32 limit;
} State;

typedef struct {
    u8 pad00[0x98];
    void **primary;
    void **secondary;
} Outputs;

typedef struct {
    State * state;
    u8 pad04[0x10];
    u32 flags;
    u8 pad18[0x90];
    Outputs *outputs;
} Object;

extern u8 D_800786DC[];
extern u8 D_800786E8[];


void update_alternate_menu_page_bounds(Object *obj)
{
    State *state;
    s32 flag_bits;

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
        flag_bits = -2;
        obj->flags &= flag_bits;
        *obj->outputs->secondary = D_800786E8;
        return;
    }

    *obj->outputs->secondary = 0;
    obj->flags |= 1;
}
