#include "common.h"

typedef struct {
    u8 pad00[0x9A];
    u8 unk9A;
    u8 unk9B;
    u8 pad9C[2];
    s16 unk9E;
} State;

typedef struct {
    u8 pad00[0x2C];
    u8 *unk2C;
} Context;

typedef struct {
    u8 pad00[0x2A];
    s16 unk2A;
} IndexSource;

extern s16 D_80083228[5];
extern u8 D_801765E8[9];
extern void func_80047784(Context *, s16, s16);

void func_80171DCC(State *state, s32 unused, Context *context, IndexSource *source)
{
    state->unk9A = 0x10;
    state->unk9B = 0;
    state->unk9E = 3;
    context->unk2C = D_801765E8;
    func_80047784(context, D_801765E8[((D_80083228[0] + source->unk2A + 0x100) >> 9) & 7], 0);
}
