/* Relink of matched dungeon/func_80D12E64; every changed retail word is a paired relocation. */
#define D_80174EA0 D_80168EC8
#include "common.h"
#include "shared/game_work.h"

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

extern u8 D_80168EC8[9];
extern void func_80047784(Context *, s16, s16);

// Initializes the state and applies a table entry selected by the combined source and global index.
void func_80166BD8(State *state, s32 unused, Context *context, IndexSource *source)
{
    state->unk9A = 0x10;
    state->unk9B = 0;
    state->unk9E = 2;
    context->unk2C = D_80168EC8;
    func_80047784(context, D_80168EC8[((gameWork.view.viewAngle + source->unk2A + 0x100) >> 9) & 7], 0);
}
