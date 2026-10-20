#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

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

/* MECHANISM: Holding menu/index in s0/s1 and delaying the second scaled index restores the 32-byte
   frame. The true-space s32 function uses return 0 for the in-row epilogue edge, removing the phantom
   call. */
