#include "common.h"

typedef struct TownDispatch {
    u8 pad00[0x54];
    s8 (*get_value)(s32);
} TownDispatch;

typedef struct TownState {
    u8 pad00[8];
    s32 index;
    u8 pad0C[0x14];
    TownDispatch *dispatch;
    u8 pad24[0x1C];
    u8 *entries;
} TownState;

extern void func_800169F8(void *);
extern void func_80017B3C(void *, s32);
extern s32 func_80017F8C(void *, s32, s32);
extern void func_80018044(void *, s32 *, s32, s32);
extern s32 func_8001894C(s32);

extern s8 D_80016000[];
extern s16 D_80018AEA;
extern s32 D_80018B40;
extern s32 D_80018E38;

void func_80016C24(s32 arg0, s32 arg1, s32 arg2)
{
    TownState *dispatch_state;
    TownState *update_state;
    TownState *final_state;
    u8 *entries;
    s32 index;
    s8 value;
    void *base = &D_80018B40;

    func_80017B3C(base, arg0);
    if (func_8001894C(D_80018AEA) == 0) {
        if (func_80017F8C(base, arg0, arg2) == 0) {
            dispatch_state = *(TownState **)D_80016000;
            value = dispatch_state->dispatch->get_value(3);
            update_state = *(TownState **)D_80016000;
            index = update_state->index;
            ASM_SCHED_BARRIER();
            entries = update_state->entries;
            entries[(index * 8) + 1] = value;
            func_800169F8(entries);
        }
    }
    final_state = *(TownState **)D_80016000;
    func_80018044(
        (u8 *)&D_80018B40 +
            (final_state->entries[(final_state->index * 8) + 1] * 8),
        &D_80018E38,
        arg0,
        arg2);
}

/* MECHANISM: The dead middle argument and held D_80018B40 base produce the 0x20
   s0/s1/s2/ra frame; separate dispatch/update/final roots give each load its retail role.
   A zero-op fence between index and entries fills the load delay and removes the cascade. */
