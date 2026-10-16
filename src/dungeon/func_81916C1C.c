#include "modules/dungeon_ovl_1936800.h"

void func_8002441C(void *context, s32 unused, Row_81916C1C_Arg81916C1C *countdown)
{
    Row_81916C1C_Inner81916C1C *tick_state;
    Row_81916C1C_State81916C1C *render_state;
    Row_81916C1C_Prim81916C1C *prim;
    s32 step;
    s8 x_value;
    s8 remaining;

    tick_state = *(Row_81916C1C_Inner81916C1C **)context;
    tick_state->counter++;
    render_state = gameWork.unk_000;
    prim = render_state->next;
    render_state->next = prim + 1;
    prim->x3 = 0x140;
    prim->x2 = 0;
    prim->y2 = 0;
    prim->y3 = 0xE0;
    step = countdown->count;
    prim->y0 = 0xC0;
    x_value = -0x40 - step * 0x30;
    prim->x1 = x_value;
    prim->x0 = x_value;
    func_800667A8(prim, step);
    prim->flags |= 2;
    func_8006658C((u8 *)gameWork.unk_000 + 0xB0, prim);
    remaining = (u8)countdown->count - 1;
    countdown->count = remaining;
    if ((remaining << 24) == 0) {
        *(u16 *)((u8 *)context - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
