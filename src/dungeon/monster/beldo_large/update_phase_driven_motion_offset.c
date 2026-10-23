#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80175D54.h"

typedef struct S_8016F5D8_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x26];
    s32 unk_2C;
} S_8016F5D8_0;   /* arg2 in update_phase_driven_motion_offset */

typedef struct S_8016F5D8_1 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0xA];
    u16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
} S_8016F5D8_1;   /* arg0 in update_phase_driven_motion_offset */

typedef struct S_8016F5D8_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016F5D8_2;   /* arg1 in update_phase_driven_motion_offset */


s32 rsin();                        /* extern */
extern u8 beldo_large_frame_set_8[16];
extern u8 D_80173DB4[16];
extern u8 *beldo_script_node;

/* Advances the phase-driven offset and writes the adjusted output value. */
/* Updates Beldo's vertical bob from the current sprite table, with different phase speeds and amplitudes
 * by frame. */
void update_phase_driven_motion_offset(S_8016F5D8_1 *state, S_8016F5D8_2 *output, S_8016F5D8_0 *command) {
    s32 command_table;
    s32 phase;
    s32 fast_count;
    s16 fast_wide_count;
    s32 slow_count;
    s16 signed_count;

    command_table = command->unk_2C;
    if (command_table == &beldo_large_frame_set_8) {
        if (command->unk_04 == 0x100) {
            state->unk_9E = 0U;
            state->unk_A0.at00.v = 0;
        }
        if ((u32) ((u8) command->unk_04 - 1) < 4U) {
            slow_count = state->unk_9E++;
            signed_count = slow_count;
            phase = signed_count * 0xAA;
            state->unk_A0.at00.v += rsin(phase) << 5;
        } else {
            slow_count = state->unk_9E++;
            signed_count = slow_count;
            phase = signed_count * 0xAA;
            state->unk_A0.at00.v += rsin(phase) << 6;
        }
    } else if (command_table == &D_80173DB4) {
        if (command->unk_04 == 0x100) {
            state->unk_9E = 0U;
            state->unk_A0.at00.v = 0;
        }
        if ((u32) ((u8) command->unk_04 - 1) < 4U) {
            fast_count = state->unk_9E;
            state->unk_9E = fast_count + 1;
            signed_count = fast_count;
            phase = signed_count * 0x155;
            fast_count++;
            state->unk_A0.at00.v += rsin(phase, fast_count) << 5;
        } else {
            fast_wide_count = state->unk_9E;
            signed_count = fast_wide_count++;
            phase = signed_count * 0x155;
            state->unk_9E = fast_wide_count;
            state->unk_A0.at00.v += rsin(phase) << 6;
        }
    }
    output->unk_0A = (s16) ((((Rec_D_80175D54 *)beldo_script_node)->unk_A8 + state->unk_92) - state->unk_A0.at02.v);
}
