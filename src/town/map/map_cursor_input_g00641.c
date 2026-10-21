/* Map cursor input (G00641). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800BBAA4. */
#include "town/map/map_cursor_input_g00641.h"

/* Store the state byte and invoke the handler at the stored tile center. */
void store_state_and_update_tile_center(s32 state)
{
    town_map_selection_state[6] = state;
    request_scene_state_with_parameters(0xC, ((town_map_selection_state[0] + 1) << 6) | 0x20,
                  ((town_map_selection_state[1] + 1) << 6) | 0x20, -0x100,
                  runtime_dispatch_state.flags16);
}

/* Updates two wrapping indices from input flags and calls store_state_and_update_tile_center on a button combination. */
void update_wrapping_indices_and_input(void) {
    GameWork *input_state = &g_game_work;
    s32 input_flags = ((s32)input_state->pressed_buttons);
    u32 buttons;
    s32 masked_buttons;

    if (input_flags < 0) {
        D_800D185C += 0x20;
    }
    if (input_flags & 0x20000000) {
        D_800D185C++;
    }
    D_800D185C %= 33;
    if (input_flags & 0x40000000) {
        D_800D185D += 0x42;
    }
    if (input_flags & 0x10000000) {
        D_800D185D++;
    }
    buttons = D_800D185D;
    buttons -= buttons / 67 * 67;
    *(u8 *) &D_800D185D = buttons;
    buttons = *(s32 *) &input_state->buttons;
    masked_buttons = buttons & 0x500000;
    if (masked_buttons == 0x500000) {
        store_state_and_update_tile_center(D_800D185D);
    }
}
