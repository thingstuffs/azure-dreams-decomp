#include "script_symbols.h"
#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"

typedef struct {
    u16 values[4];
} TownValues;

extern u8 D_80010000[];
extern s32 D_80017530;

extern s32 D_80017598;
extern s32 D_800175A4;
extern s32 get_script_flag_mask(s32 flagIndex);

/* Selects a data pointer based on queried conditions and the current state index. */
void select_data_pointer_by_conditions(void **out_data) {
    TownValues condition_ids;
    register void *selected_data;
    s32 state_index;
    register TownValues *condition_table;

    condition_table = (TownValues *)(D_80010000 + 0x7134);
    condition_ids = *condition_table;
    if (get_script_flag_mask(F_veld_kill) != 0) {
        selected_data = &D_80017530;
    } else if (get_script_flag_mask(sn_open_sekkyo_end) != 0) {
        state_index = town_scene_root->entry_index;
        if (get_script_flag_mask(condition_ids.values[state_index]) == 0) {
            selected_data = &D_80017598;
        } else {
            selected_data = &D_800175A4;
        }
    } else {
        selected_data = select_alternate_data_for_conditions;
    }
    *out_data = selected_data;
}
