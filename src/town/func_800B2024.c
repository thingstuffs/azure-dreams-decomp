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
extern void func_800AF7E0(void);

void func_800AF784(Object *obj)
{
    register State *state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 mask;

    if (obj->state->current > 0) {
        u32 value;

        *obj->outputs->primary = D_800786DC;
        value = obj->flags;
        value &= ~2;
        ASM_TAILSLOT_PIN(value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800AF7E0();
        return;
    }

    *obj->outputs->primary = 0;
    obj->flags |= 2;
    state = obj->state;
    if (state->current < state->limit) {
        mask = -2;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        obj->flags &= mask;
        *obj->outputs->secondary = D_800786E8;
        return;
    }

    *obj->outputs->secondary = 0;
    obj->flags |= 1;
}
