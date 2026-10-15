#include "common.h"

/* Recovered complete gap routine; not registered or assigned to a native module. */
typedef struct {
    s32 current, maximum;
    u8 pad08[0x24];
    u8 cursor[0x14];
    void *resource_names;
    u8 pad44[0x44];
    void *entries;
} ProgressState;
extern void func_80027B44(void *, s32, s32);
extern void func_80027AD0(void *, s32, s32);
extern void func_80027B6C(void *, s32, s32);
extern void func_80027BBC(void *, void *);
extern void func_8004CB2C(void *);
void func_80027D08(ProgressState *state) {
    func_80027B44(state->entries, state->current, state->maximum);
    func_80027AD0(state, state->current, state->maximum);
    func_80027B6C(state->entries, state->current, state->maximum);
    func_80027BBC(state->entries, state->resource_names);
    func_8004CB2C(state->cursor);
}
