#include "common.h"
#include "shared/record_ptrs.h"
#include "town/player/script_flags.h"
#include "shared/town_root.h"
#include "town/scene.h"
#include "town/scene/motion.h"
#include "town/scene/flags.h"

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

extern void decrement_entry_counter_if_flag(void *);

extern s16 scene_request_flag_id;
extern s32 D_80018B40;
extern s32 D_80018E38;

/* Refresh the active entry value and apply its corresponding table record. */
void refresh_scene_active_entry(void *update_arg, s32 unused, s32 entry_arg)
{
    TownState *dispatch_state;
    TownState *update_state;
    TownState *final_state;
    u8 *entries;
    s32 entry_index;
    s8 value_index;
    void *value_table = &D_80018B40;

    apply_entry_keyed_values(value_table, update_arg, entry_arg);
    if (get_script_flag_mask(scene_request_flag_id) == 0) {
        if (resolve_entry_flag(value_table, update_arg, entry_arg) == 0) {
            dispatch_state = (TownState *)town_scene_root;
            value_index = dispatch_state->dispatch->get_value(3);
            update_state = (TownState *)town_scene_root;
            entry_index = update_state->index;
            entries = update_state->entries;
            /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: town/func_804B8424). */
            do {
                entries[(entry_index * 8) + 1] = value_index;
            } while (0);
            decrement_entry_counter_if_flag(entries);
        }
    }
    final_state = (TownState *)town_scene_root;
    apply_entry_position(
        (u8 *)&D_80018B40 +
            (final_state->entries[(final_state->index * 8) + 1] * 8),
        &D_80018E38,
        update_arg,
        entry_arg);
}
