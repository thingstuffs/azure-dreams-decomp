/* Relink of matched dungeon/func_80BC1880; every changed retail word is a paired relocation. */
#define dungeonSpawnConfiguredOverlayObjectB func_8016B080
#include "modules/dungeon_ovl_be1084.h"
extern s32  func_80065420(void *,void *,void *,void *);

void func_8016B080(void *effect, S_80BC1880_2 *position, S_80BC1880_0 *render_state)
{
    StackWork projection;
    s16 ticks_left;

    render_state->unk_1C -= 500;
    render_state->unk_1E -= 500;
    render_state->unk_1A += 400;

    render_state->unk_0C =
        ((S_80BC1880_1 *)effect)->unk_02 *
        (((S_80BC1880_1 *)effect)->unk_1C - ((S_80BC1880_1 *)effect)->unk_1A.s) /
        ((S_80BC1880_1 *)effect)->unk_1C;
    render_state->unk_0D =
        ((S_80BC1880_1 *)effect)->unk_03 *
        (((S_80BC1880_1 *)effect)->unk_1C - ((S_80BC1880_1 *)effect)->unk_1A.s) /
        ((S_80BC1880_1 *)effect)->unk_1C;
    render_state->unk_0E =
        ((S_80BC1880_1 *)effect)->unk_04 *
        (((S_80BC1880_1 *)effect)->unk_1C - ((S_80BC1880_1 *)effect)->unk_1A.s) /
        ((S_80BC1880_1 *)effect)->unk_1C;

    projection.xyz[0] = position->unk_02;
    projection.xyz[1] = position->unk_06;
    projection.xyz[2] = position->unk_0A;
    render_state->unk_06 =
        func_80065420(projection.xyz, &projection.out18, &projection.out20, &projection.out24) - 8;

    ticks_left = ((S_80BC1880_1 *)effect)->unk_1A.u - 1;
    ((S_80BC1880_1 *)effect)->unk_1A.u = ticks_left;
    if ((ticks_left << 16) <= 0) {
        ((S_80BC1880_1_pre *)effect)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
