#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

s32 initialize_indexed_entry_on_first_479(S_80017824_0 *obj, s32 index) {
    s32 offset;
    S_80017824_1 *entry;

    if ((func_8001A510(F_sbs04_pad03) == 0) && (check_interaction_13_type_3() != 0)) {
        func_8001A418(F_sbs04_pad03);
        offset = index * 0x10;
        ((S_80017824_2 *)((offset + obj->unk_10)))->handler = select_interaction_result_with_refresh;
        entry = offset + obj->unk_10;
        entry->unk_08 = &D_8001B718;
        mark_progress_state_ready();
    }
    return 0;
}
