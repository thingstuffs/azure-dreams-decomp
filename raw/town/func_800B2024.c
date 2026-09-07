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
extern void func_800AF850(void);

void func_800AF784(Object *obj)
{
    register State *state ASM_REG("$2");
    s32 mask;

    if (obj->state->current > 0) {
        register u32 value ASM_REG("$2");

        *obj->outputs->primary = D_800786DC;
        value = obj->flags;
        value &= ~2;
        ASM_TAILSLOT_PIN(value);
        func_800AF7E0();
        return;
    }

    *obj->outputs->primary = 0;
    obj->flags |= 2;
    state = obj->state;
    if (state->current < state->limit) {
        mask = -2;
        ASM_SCHED_BARRIER();
        obj->flags &= mask;
        *obj->outputs->secondary = D_800786E8;
        func_800AF850();
        return;
    }

    *obj->outputs->secondary = 0;
    obj->flags |= 1;
}
