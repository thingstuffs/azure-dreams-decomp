#include "common.h"

extern void func_80094984(void *arg0, void *arg1, s32 arg2);
extern void func_8009AE88(void *arg0, s32 arg1, s32 arg2);
extern u8 D_800D0078[];
extern void *D_8009AFF4[];

typedef struct {
    s32 unk0;
    void **unk4;
    u16 unk8;
    u16 unkA;
} Struct8009D814;

/* Decrement the countdown, switch the state's table on expiry, and update the state. */
void func_8009AF74(Struct8009D814 *state, s32 update_arg, s32 shared_arg) {
    s16 countdown;

    countdown = state->unkA - 1;
    state->unkA = countdown;
    if (countdown <= 0) {
        func_80094984(D_800D0078, state, shared_arg);
        state->unk4 = D_8009AFF4;
    }
    func_8009AE88(state, update_arg, shared_arg);
}
