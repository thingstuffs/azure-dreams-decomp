#include "common.h"

/* Recovered complete gap routine; not registered or assigned to a native module. */
typedef struct { void *callback; u8 pad4[6]; s16 count; } InitState;
extern void func_80094984(void *, InitState *, void *);
extern u8 D_800D0128[];
extern void func_800927EC(void);
void func_8009451C(InitState *state, void *unused, void *context) {
    func_80094984(D_800D0128, state, context);
    state->callback = (void *)func_800927EC;
}
