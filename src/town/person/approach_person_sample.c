#include "common.h"
#include "town/person.h"
#include "town/person/motion.h"





typedef struct S_800AB5C0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800AB5C0_1;   /* arg1 in approach_person_sample */

/* Smooth coordinates toward the adjusted sample, snapping to it when the timer expires. */
void approach_person_sample(TownObjectRecord *state, S_800AB5C0_1 *coords) {
    Fixed1616 sampled_coords[6];
    s32 z_offset;
    u16 ticks_left;

    if (state->unk_90 < 100) {
        state->state_callback.as_pm = move_person_toward_sample;
    }
    load_position_history_entry(sampled_coords, 4);
    z_offset = get_map_cell_step_size(coords);
    sampled_coords[2].w.i -= z_offset + advance_person_sine_offset(state);
    ticks_left = state->timer - 1;
    state->timer = ticks_left;
    if ((s16)ticks_left < 0) {
        coords->unk_0E = coords->unk_02 = sampled_coords[0].w.i;
        coords->unk_12 = coords->unk_06 = sampled_coords[1].w.i;
        coords->unk_16 = coords->unk_0A = sampled_coords[2].w.i;
        state->state_callback.as_pm = update_person_coordinates;
        state->timer = 150;
        return;
    }
    coords->unk_02 = (coords->unk_02 + sampled_coords[0].w.i) / 2;
    coords->unk_06 = (coords->unk_06 + sampled_coords[1].w.i) / 2;
    coords->unk_0A = (coords->unk_0A + sampled_coords[2].w.i) / 2;
}
