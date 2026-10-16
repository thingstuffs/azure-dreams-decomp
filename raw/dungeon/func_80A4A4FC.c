#include "common.h"

typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} ResourceActor;

extern s32 func_800AC010(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_8017140C();

/* Enter the update callback when both contact checks succeed. */
void func_80173CFC(ResourceActor *state, void *entity, void *position, void *graphic)
{
    if (func_800AC010(state, entity, position, graphic)) {
        if ((s16)func_800AD9B4(position, graphic) > 0) {
            state->callback = func_8017140C;
        }
    }
}
