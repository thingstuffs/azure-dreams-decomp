#include "script_symbols.h"
#include "common.h"
#include "town/scene/mode_data.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town/scene/event.h"
#include "town/scene/flags.h"

typedef struct S_800167E4_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800167E4_0;   /* arg0 in clear_flagged_status_and_dispatch_action */

typedef struct S_800167E4_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_800167E4_1;   /* town in clear_flagged_status_and_dispatch_action */

typedef struct S_800167E4_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_800167E4_2;   /* town2 in clear_flagged_status_and_dispatch_action */

typedef struct S_800167E4_3 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_800167E4_3;   /* ((S_800167E4_1 *)town)->unk_08 * 8 + ((S_800167E4_1 *)town)->unk_40 in clear_flagged_status_and_dispatch_action */

typedef struct S_800167E4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_800167E4_4;   /* index * 8 + ((S_800167E4_2 *)town2)->unk_40 in clear_flagged_status_and_dispatch_action */

extern s16 D_80019676;

/* Clears flagged town status and dispatches the action when its conditions are met. */
s32 clear_flagged_status_and_dispatch_action(S_800167E4_0 *entity, s32 action_arg)
{
    S_800167E4_1 *town;
    s32 flag_id;

    town = (void *)town_scene_root;
    flag_id = entity->unk_18;
    scene_cell_dispatch_code = ((S_800167E4_3 *)(town->unk_08 * 8 + town->unk_40))->unk_04;

    if (get_script_flag_mask(flag_id) != 0) {
        {
            S_800167E4_2 *clear_town;
            s32 entry_index;

            clear_town = (void *)town_scene_root;
            entry_index = clear_town->unk_08;
            ((S_800167E4_4 *)(entry_index * 8 + clear_town->unk_40))->unk_04 = 0;
        }
        flag_id = entity->unk_18;
        scene_cell_dispatch_code = 0;
        clear_script_flag_bit(flag_id);
    }

    if (are_all_checks_set() != 0 && get_script_flag_mask(F_sbs14_pad19) != 0) {
        if (get_script_flag_mask(D_80019676) == 0 && scene_cell_dispatch_code == 0) {
            clear_script_flag_bit(F_sbs14_pad19);
            set_indexed_entry_flag(entity, action_arg);
            return 1;
        }
    } else {
        set_script_flag_bit(F_sbs14_pad19);
    }

    invoke_callback_event_11();
    return 0;
}
