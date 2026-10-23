#include "common.h"
#include "records/Rec_func_80036210_arg0.h"

#include "common.h"
#include "engine/window.h"

typedef struct S_800364BC_2 {
    u8 pad_00[0x84];
    s8 unk_84;
} S_800364BC_2;   /* ((S_800364BC_1 *)arg0)->unk_74 in runtime_mark_state_when_flag_51_set */

typedef struct S_800364BC_0 {
    u8 pad_00[0x51];
    u8 unk_51;
    u8 pad_52[0x16];
    s32 * unk_68;
} S_800364BC_0;   /* arg0 in runtime_mark_state_when_flag_51_set */

/* If the flag at offset 0x51 is set, marks the linked state and selects func_80036154. */
void runtime_mark_state_when_flag_51_set(S_800364BC_0 *state) {
    if (state->unk_51 != 0) {
        ((S_800364BC_2 *)(((Rec_func_80036210_arg0 *)state)->unk_74.as_pv))->unk_84 = 1;
        state->unk_68 = &select_menu_initializer_from_message_handler;
    }
}
