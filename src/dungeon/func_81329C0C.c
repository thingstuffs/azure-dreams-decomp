#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 pad6[2];
} S_80174CF0;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 pad4[3];
} S_800DCE60;

extern S_80174CF0 D_80174CF0;
extern S_800DCE60 D_800DCE60;
extern s32 D_800832B4[3];
extern void func_8004D7A8(s32);
extern void func_8004D294();

/* Initializes the destination state from the source and submits it for processing. */
void func_8017140C(void)
{
    S_80174CF0 *destinationState = &D_80174CF0;

    destinationState->unk4 = 0;
    D_800832B4[0] = 0;
    D_80174CF0.unk0 = D_800DCE60.unk0;
    destinationState->unk2 = D_800DCE60.unk2;
    func_8004D7A8(1);
    func_8004D294(0, destinationState, 10);
}
