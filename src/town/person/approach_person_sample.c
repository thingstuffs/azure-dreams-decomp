#include "common.h"
#include "records/Rec_func_800AB030_arg0.h"
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
void approach_person_sample(Rec_func_800AB030_arg0 *state, S_800AB5C0_1 *coords) {
    s16 sampled_coords[12];
    s32 z_offset;
    u16 ticks_left;

    if (state->unk_90 < 100) {
        state->unk_50 = move_person_toward_sample;
    }
    load_record_halfwords_3(sampled_coords, 4);
    z_offset = get_person_lookup_step(coords);
    sampled_coords[5] -= z_offset + advance_person_lookup_value(state);
    ticks_left = state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if ((s16)ticks_left < 0) {
        coords->unk_0E = coords->unk_02 = sampled_coords[1];
        coords->unk_12 = coords->unk_06 = sampled_coords[3];
        coords->unk_16 = coords->unk_0A = sampled_coords[5];
        state->unk_50 = update_person_coordinates;
        state->unk_6C = 150;
        return;
    }
    coords->unk_02 = (coords->unk_02 + sampled_coords[1]) / 2;
    coords->unk_06 = (coords->unk_06 + sampled_coords[3]) / 2;
    coords->unk_0A = (coords->unk_0A + sampled_coords[5]) / 2;
}
