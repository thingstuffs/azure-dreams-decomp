#include "common.h"

#include "common.h"
#include "shared/position_views.h"
#include "engine/window.h"

typedef struct S_80036110_0 {
    void * unk_00;
    u8 pad_04[0x64];
    s32 * unk_68;
} S_80036110_0;   /* arg0 in scroll_window_y */

   /* temp_v0 in scroll_window_y */

   /* temp_v1 in scroll_window_y */

/* Decreases the state field at offset 0x0A by 0x140, clamping below zero and advancing the handler. */
void scroll_window_y(S_80036110_0 *object) {
    UnsignedCountdownView *state;
    UnsignedCountdownView *updated_state;

    state = object->unk_00;
    state->unk_0A = (u16) (state->unk_0A - 0x140);
    updated_state = object->unk_00;
    if ((s16) updated_state->unk_0A < 0) {
        updated_state->unk_0A = 0U;
        object->unk_68 = &select_menu_initializer_from_message_handler;
    }
}
