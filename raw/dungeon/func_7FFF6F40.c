#include "common.h"

/* Recovered complete gap routine; not registered or assigned to a native module. */
typedef struct { void *callback; u8 pad4[6]; s16 count; } InitState;
extern void func_80094C1C(InitState *, void *, void *);
extern void func_80094984(void *, InitState *, void *);
extern u8 D_800D0138[];
extern void func_80092FF0(void);
void func_800946A0(InitState *state, void *argument, void *context) {
    func_80094C1C(state, argument, context);
    func_80094984(D_800D0138, state, context);
    state->callback = (void *)func_80092FF0;
    state->count = 6;
}
