#include "common.h"

typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} ResourceActor;

extern s32 func_800AB378(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80170E54();

/* Enter the update callback when both contact checks succeed. */
void func_801727E8(ResourceActor *state, void *entity, void *position, void *graphic)
{
    if (func_800AB378(state, entity, position, graphic)) {
        if ((s16)func_800AD9B4(position, graphic) > 0) {
            state->callback = func_80170E54;
        }
    }
}
