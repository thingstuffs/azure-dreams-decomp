#include "common.h"

typedef struct {
    s32 unk00;
    s8 unk04;
    s8 unk05;
} Struct8009ED34Arg2;

typedef struct {
    s8 pad00[0x50];
    void *unk50;
    s8 pad54[0x6C - 0x54];
    s16 unk6C;
} Struct8009ED34Arg0;

extern s32 func_8004491C(void *arg0, void *arg1);
extern u8 D_80045340[];
extern u8 D_8009C4E8[];

/* Clear state, initialize the context resource, and set a 30-tick countdown and handler. */
void func_8009C494(Struct8009ED34Arg0 *context, void *unused, Struct8009ED34Arg2 *state) {
    state->unk00 = 0;
    state->unk04 = 0;
    state->unk05 = 0;
    func_8004491C((void *)((s8 *)context - 0x20), D_80045340);
    context->unk6C = 30;
    context->unk50 = D_8009C4E8;
}
