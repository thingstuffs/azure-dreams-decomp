#include "common.h"

extern s32 func_8004437C(s16 arg0, s16 arg1);
extern s16 func_80053DA8(s32 arg0);
extern void func_800542BC(void);
extern s8 D_80080A88[];
extern s16 D_800D4258[];
extern s16 D_800D4260[];
extern s16 D_800D4262[];
extern s16 D_800D4264[];
extern s16 D_800D4266[];
extern s16 D_800D4268[];

void func_800C122C(void)
{
    s16 *pending;
    s16 *active;
    s16 *previous;
    s16 *output;
    s32 selection;
    s16 minus_one;
    u16 output0;

    pending = D_800D4258;
    if (pending[1] == -5) { pending[1] = -1; D_800D4262[0] = -1; }
    if (pending[2] == -5) { pending[2] = -1; D_800D4264[0] = -1; }
    if (pending[3] == -5) { pending[3] = -1; D_800D4266[0] = -1; }
    minus_one = -1;
    if (pending[1] != minus_one) D_800D4262[0] = (u16)pending[1];
    if (pending[2] != minus_one) D_800D4264[0] = (u16)pending[2];
    if (pending[3] != minus_one) D_800D4266[0] = (u16)pending[3];

    active = D_800D4260;
    selection = active[2];
    if (selection == minus_one) goto no_selection;
    previous = D_800D4268;
    if (previous[2] != selection) {
        func_80053DA8(0x71);
        func_800542BC();
        func_8004437C(active[2], 0);
        if (active[3] == minus_one) goto finish;
        goto play_active_floor;
    }
    if (active[3] == minus_one) goto inactive_floor;
    if (previous[3] != active[3]) {
        func_80053DA8(0x71);
        func_800542BC();
        goto play_active_floor;
    }
    if (D_80080A88[0] != 0) goto finish;
    func_80053DA8(0x71);
    func_800542BC();
    ASM_SCHED_BARRIER();
    goto play_active_floor;

inactive_floor:
    func_80053DA8(0x71);
    func_800542BC();
    goto finish;

no_selection:
    func_80053DA8(0x71);
    func_800542BC();
    if (active[3] != selection) {
play_active_floor:
        func_80053DA8((u16)active[3]);
    }

finish:
    active = D_800D4260;
    minus_one = -1;
    if (active[1] != minus_one) func_80053DA8((u16)active[1]);
    D_800D4258[0] = minus_one;
    {
        s16 *finish_pending = D_800D4258;
        finish_pending[1] = minus_one;
        finish_pending[2] = minus_one;
        finish_pending[3] = minus_one;
    }
    output0 = D_800D4260[0];
    D_80080A88[0] = 0;
    D_800D4268[0] = output0;
    {
        u16 output1 = active[1];
        u16 output2 = active[2];
        u16 output3 = active[3];
        output = D_800D4268;
        output[1] = output1;
        output[2] = output2;
        output[3] = output3;
    }
}
