#include "common.h"

extern s32 func_8004437C(s16 arg0, s16 arg1);
extern s16 SD_Call(s32 arg0);
extern void func_800542BC(void);
extern s8 D_80080A88[];
extern s16 D_800D4258[];
extern s16 D_800D4260[];
extern s16 D_800D4262[];
extern s16 D_800D4264[];
extern s16 D_800D4266[];
extern s16 D_800D4268[];

/* Apply pending selections, update playback, and save the active state. */
void func_800C122C(void)
{
    s16 *pending;
    s16 *active;
    s16 *previous;
    s16 *snapshot;
    s32 selection;
    s16 unset;
    u16 saved_slot_0;

    pending = D_800D4258;
    if (pending[1] == -5) { pending[1] = -1; D_800D4262[0] = -1; }
    if (pending[2] == -5) { pending[2] = -1; D_800D4264[0] = -1; }
    if (pending[3] == -5) { pending[3] = -1; D_800D4266[0] = -1; }
    unset = -1;
    if (pending[1] != unset) D_800D4262[0] = (u16)pending[1];
    if (pending[2] != unset) D_800D4264[0] = (u16)pending[2];
    if (pending[3] != unset) D_800D4266[0] = (u16)pending[3];

    active = D_800D4260;
    selection = active[2];
    if (selection == unset) goto no_selection;
    previous = D_800D4268;
    if (previous[2] != selection) {
        SD_Call(0x71);
        func_800542BC();
        func_8004437C(active[2], 0);
        if (active[3] == unset) goto finish;
        goto play_active_floor;
    }
    if (active[3] == unset) goto inactive_floor;
    if (previous[3] != active[3]) {
        SD_Call(0x71);
        func_800542BC();
        goto play_active_floor;
    }
    if (D_80080A88[0] != 0) goto finish;
    SD_Call(0x71);
    func_800542BC();
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    goto play_active_floor;

inactive_floor:
    SD_Call(0x71);
    func_800542BC();
    goto finish;

no_selection:
    SD_Call(0x71);
    func_800542BC();
    if (active[3] != selection) {
play_active_floor:
        SD_Call((u16)active[3]);
    }

finish:
    active = D_800D4260;
    unset = -1;
    if (active[1] != unset) SD_Call((u16)active[1]);
    D_800D4258[0] = unset;
    {
        s16 *pending_reset = D_800D4258;
        pending_reset[1] = unset;
        pending_reset[2] = unset;
        pending_reset[3] = unset;
    }
    saved_slot_0 = D_800D4260[0];
    D_80080A88[0] = 0;
    D_800D4268[0] = saved_slot_0;
    {
        u16 saved_slot_1 = active[1];
        u16 saved_selection = active[2];
        u16 saved_floor = active[3];
        snapshot = D_800D4268;
        snapshot[1] = saved_slot_1;
        snapshot[2] = saved_selection;
        snapshot[3] = saved_floor;
    }
}
