#include "common.h"

#include "common.h"

typedef struct {
    u8 pad0[0x0C];
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 padF;
    u16 unk10;
    u8 pad12[2];
    u16 unk14;
} State;

typedef struct {
    void (*callback)(void);
    u8 rest[0x0C];
} Manager;

extern Manager D_80082D58;
extern void runtime_set_destination_flag_from_source(void *dest, void *source);
extern void func_8003C4C8(void);

/* Prepare the state when needed, set the manager callback, and process the state. */
void func_8003C24C(void) {
    void *manager = &D_80082D58;
    State *state = *(State **)((u8 *)manager - 0x14);

    if (state->unkC == 0x80) {
        state->unkE = 0x60;
        state->unkD = 0x60;
        state->unkC = 0x60;
        state->unk10 = 0x20;
        state->unk14 |= 0x1C;
        D_80082D58.callback = func_8003C4C8;
    } else {
        D_80082D58.callback = func_8003C4C8;
    }

    runtime_set_destination_flag_from_source(manager, state);
}
