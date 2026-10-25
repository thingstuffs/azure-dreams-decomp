#include "common.h"
#include "records/Rec_func_80036210_arg0.h"

#include "common.h"
#include "engine/window.h"

typedef struct S_800362A0_2 {
    u8 pad_00[0x84];
    s8 unk_84;
} S_800362A0_2;   /* ((S_800362A0_1 *)arg0)->unk_74 in runtime_mark_state_when_flag_50_set */

typedef struct S_800362A0_0 {
    u8 pad_00[0x50];
    u8 unk_50;
    u8 pad_51[0x17];
    void (*unk_68)(void *);
} S_800362A0_0;   /* arg0 in runtime_mark_state_when_flag_50_set */

/* If the flag at offset 0x50 is set, marks the linked state and selects func_80036154. */
void runtime_mark_state_when_flag_50_set(S_800362A0_0 *state) {
    if (state->unk_50 != 0) {
        ((S_800362A0_2 *)(((Rec_func_80036210_arg0 *)state)->unk_74.as_pv))->unk_84 = 1;
        state->unk_68 = &select_menu_initializer_from_message_handler;
    }
}
