/* Prepare progress interactions (G00708). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80470808, PD:town/image_3ef000:8001B718. */
#include "town/scene/progress_interaction_g00708.h"
#include "town/scene.h"

void mark_progress_state_ready(void) {
    town_scene_root->event_data->unk_B0 = 1;
}

/* Installs an indexed interaction handler and data once, sets its flag, and marks the state ready. */
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

/* Installs the first interaction handler once, then selects the follow-up handler and dispatches it. */
s32 start_interaction_on_code_0x479(S_800178B4_0 *menu, s32 index) {
    s32 offset;
    s32 offset2;
    S_800178B4_2 *slot;

    if ((func_8001A510(F_sbs04_pad03) == 0) && (check_interaction_13_type_3() != 0)) {
        func_8001A418(F_sbs04_pad03);
        offset = index * 0x10;
        {
            SceneHandler3 handler;
            s32 slot_addr;

            slot_addr = offset + menu->unk_10;
            handler = select_interaction_result_with_refresh;
            ((S_800178B4_1 *)slot_addr)->handler = handler;
        }
        slot = offset + menu->unk_10;
        slot->unk_08 = &D_8001B718;
        mark_progress_state_ready();
        return 0;
    }
    if (func_8001A510(F_sbs04_pad03) != 0) {
        offset2 = index * 0x10;
        ((S_800178B4_3 *)((offset2 + menu->unk_10)))->handler = lookup_entry_with_fallback_e;
        ((S_800178B4_3 *)((offset2 + menu->unk_10)))->unk_08 = &D_8001B81C;
    }
    func_8001A418(menu->unk_18);
    return func_80019814(menu, index);
}
