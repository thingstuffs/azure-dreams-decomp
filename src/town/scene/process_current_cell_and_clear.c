#include "script_symbols.h"
#include "common.h"
#include "town/scene/entry_requests.h"
#include "shared/record_ptrs.h"
#include "town.h"
#include "town/scene.h"
#include "shared/town_root.h"
#include "town/data.h"
#include "town/player/state.h"
#include "town/scene/service.h"

typedef struct S_80016B0C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    u8 * unk_40;
} S_80016B0C_0;   /* state in process_current_cell_and_clear */


typedef struct S_80016B0C_2 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_80016B0C_2;   /* (u8 *)((S_80016B0C_1 *)(*(void **)D_80016000))->unk_40
                + ((S_80016B0C_1 *)(*(void **)D_80016000))->unk_08 * 8 in process_current_cell_and_clear */


extern s32 scene_cell_dispatch_code;

extern void mark_indexed_records_8000(void *, u8 *);

/* Process the current cell value and clear it when the handler returns nonzero. */
s32 process_current_cell_and_clear(void *object, s32 entry_index) {
    u8 fallback_args[2] = { 2, 0xFF };
    S_80016B0C_0 *state;
    s32 result;
    s32 cell_index;
    u8 *cells;

    state = (void *)town_scene_root;
    cell_index = state->unk_08;
    cells = state->unk_40;
    scene_cell_dispatch_code = cells[cell_index * 8 + 4];
    result = apply_selected_entry_values(object, entry_index);

    if (result != 0) {
        if (get_script_flag_mask(F_sbs14_pad14) == 0) {
            clear_script_flag_bit(F_sbs14_pad08);
            clear_script_flag_bit(F_sbs14_pad09);
        }

        ((S_80016B0C_2 *)((u8 *)town_scene_root->event_data
                + town_scene_root->entry_index * 8))->unk_04 = 0;
        scene_cell_dispatch_code = 0;
        set_scene_entry_flag_k();
    } else {
        mark_indexed_records_8000(scene_current_cell_pointer, fallback_args);
        call_scene_service_2f4_fixed();
    }

    return result;
}
