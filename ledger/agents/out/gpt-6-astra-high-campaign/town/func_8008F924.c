#include "common.h"

typedef struct {
    s8 pad[0x14];
    s16 unk14;
    s16 unk16;
} TownViewState;

extern u8 D_80083160[0x1DC];
extern s32 D_800FE480[];
extern s32 D_800FE484[];

/* Set the two view scales from the stored shift counts. */
void func_8008D084(void)
{
    TownViewState *state;

    state = (TownViewState *)D_80083160;
    
    state = (TownViewState *)((u8 *)state + 0x1DC);

    D_800FE480[0] = 0x40 << state->unk14;
    D_800FE484[0] = 0x40 << state->unk16;
}
