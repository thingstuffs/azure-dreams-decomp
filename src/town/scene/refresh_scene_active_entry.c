#include "common.h"
#include "shared/record_ptrs.h"

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

extern void decrement_current_entry_counter_condition(void *);
extern void func_80017B3C(void *, s32);
extern s32 invoke_system_callback_21_c(void *, s32, s32);
extern void func_80018044(void *, s32 *, s32, s32);
extern s32 func_8001894C(s32);

extern s16 scene_request_flag_id;
extern s32 D_80018B40;
extern s32 D_80018E38;

/* Refresh the active entry value and apply its corresponding table record. */
void refresh_scene_active_entry(s32 update_arg, s32 unused, s32 entry_arg)
{
    TownState *dispatch_state;
    TownState *update_state;
    TownState *final_state;
    u8 *entries;
    s32 entry_index;
    s8 value_index;
    void *value_table = &D_80018B40;

    func_80017B3C(value_table, update_arg);
    if (func_8001894C(scene_request_flag_id) == 0) {
        if (invoke_system_callback_21_c(value_table, update_arg, entry_arg) == 0) {
            dispatch_state = *(TownState **)((s8 *)(&D_80016000));
            value_index = dispatch_state->dispatch->get_value(3);
            update_state = *(TownState **)((s8 *)(&D_80016000));
            entry_index = update_state->index;
            entries = update_state->entries;
            do {
                entries[(entry_index * 8) + 1] = value_index;
            } while (0);
            decrement_current_entry_counter_condition(entries);
        }
    }
    final_state = *(TownState **)((s8 *)(&D_80016000));
    func_80018044(
        (u8 *)&D_80018B40 +
            (final_state->entries[(final_state->index * 8) + 1] * 8),
        &D_80018E38,
        update_arg,
        entry_arg);
}
