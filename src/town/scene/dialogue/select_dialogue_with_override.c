#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

s32 select_dialogue_with_799_override(s32 speaker, s32 interaction, s32 dialogue_id) {
    s32 dialogue;

    if (check_table_result_below_minus_47(speaker, interaction) != 0) {

        return &D_8001B63C;
    }
    dialogue = func_80019ABC(&D_8001A97C, &D_8001B1FC, speaker, dialogue_id);
    if (func_80019A04(&D_8001A97C, speaker, dialogue_id) != 0) {
        if (func_8001A510(F_sbs22_pad29) != 0) {

            dialogue = &D_8001CDF2;
        } else {
            dialogue = select_state_result_with_lookup_overrides(speaker, interaction, dialogue_id);
        }
    }
    return dialogue;
}
