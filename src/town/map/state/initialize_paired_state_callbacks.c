#include "common.h"
#include "shared/game_work.h"

extern s32 map_transition_handler_address;
extern s32 map_fallback_handler_address;

/* Initialize paired state values and install the two callbacks. */
void initialize_paired_state_callbacks(void *state) {
    u16 initial_ac;
    u16 initial_ae;

    initial_ac = ((u16)g_game_work.view.view_offset.parts.view_offset_x);
    *(u16 *) ((u8 *) state + 0) = initial_ac;
    *(u16 *) ((u8 *) state + 0x10) = initial_ac;

    initial_ae = ((u16)g_game_work.view.view_offset.parts.view_offset_y);
    *(u16 *) ((u8 *) state + 2) = initial_ae;
    *(u16 *) ((u8 *) state + 0x12) = initial_ae;

    g_game_work.view.view_offset.parts.view_offset_z = 0x400;
    *(s16 *) ((u8 *) state + 4) = 0x400;
    *(s16 *) ((u8 *) state + 0x14) = 0x400;
    *(void **) ((u8 *) state + 0x1C) = &map_fallback_handler_address;
    *(void **) ((u8 *) state + 0x20) = &map_transition_handler_address;
}
