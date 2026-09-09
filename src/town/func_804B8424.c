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

/* Refresh the active entry value and apply its corresponding table record. */
void func_80016C24(s32 update_arg, s32 unused, s32 entry_arg)
{
    TownState *dispatch_state;
    TownState *update_state;
    TownState *final_state;
    u8 *entries;
    s32 entry_index;
    s8 value_index;
    void *value_table = &D_80018B40;

    func_80017B3C(value_table, update_arg);
    if (func_8001894C(D_80018AEA) == 0) {
        if (func_80017F8C(value_table, update_arg, entry_arg) == 0) {
            dispatch_state = *(TownState **)D_80016000;
            value_index = dispatch_state->dispatch->get_value(3);
            update_state = *(TownState **)D_80016000;
            entry_index = update_state->index;
            entries = update_state->entries;
            do {
                entries[(entry_index * 8) + 1] = value_index;
            } while (0);
            func_800169F8(entries);
        }
    }
    final_state = *(TownState **)D_80016000;
    func_80018044(
        (u8 *)&D_80018B40 +
            (final_state->entries[(final_state->index * 8) + 1] * 8),
        &D_80018E38,
        update_arg,
        entry_arg);
}
