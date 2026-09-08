#include "common.h"

typedef struct {
    u8 pad00[0x9A];
    u8 unk9A;
    u8 unk9B;
    u8 pad9C[8];
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
extern u8 D_8017387C[9];
extern void func_80047784(Context *, s16, s16);

// Initializes state and configures the context from an eight-way direction lookup.
void func_80171D14(State *state, s32 unused, Context *context, IndexSource *directionSource)
{
    state->unk9A = 0x10;
    state->unk9B = 0;
    state->unk9E = 8;
    context->unk2C = D_8017387C;
    func_80047784(context, D_8017387C[((D_80083228[0] + directionSource->unk2A + 0x100) >> 9) & 7], 0);
}
