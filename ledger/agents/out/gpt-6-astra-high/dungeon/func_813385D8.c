#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016F5D8_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x26];
    s32 unk_2C;
} S_8016F5D8_0;   /* arg2 in func_8016F5D8 */

typedef struct S_8016F5D8_1 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0xA];
    u16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
} S_8016F5D8_1;   /* arg0 in func_8016F5D8 */

typedef struct S_8016F5D8_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016F5D8_2;   /* arg1 in func_8016F5D8 */

typedef struct S_8016F5D8_3 {
    u8 pad_00[0xA8];
    u16 unk_A8;
} S_8016F5D8_3;   /* D_80175D54 in func_8016F5D8 */


s32 func_800644B8();                        /* extern */
extern M2C_UNK D_80173DA4;
extern M2C_UNK D_80173DB4;
extern u8 *D_80175D54;

/* Advances the phase-driven offset and writes the adjusted output value. */
void func_8016F5D8(S_8016F5D8_1 *state, S_8016F5D8_2 *output, S_8016F5D8_0 *command) {
    s32 command_table;
    register s32 phase ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 fast_count;
    s32 fast_wide_count;
    s32 slow_count;
    s16 signed_count;

    command_table = command->unk_2C;
    if (command_table == &D_80173DA4) {
        if (command->unk_04 == 0x100) {
            state->unk_9E = 0U;
            state->unk_A0.at00.v = 0;
        }
        if ((u32) ((u8) command->unk_04 - 1) < 4U) {
            slow_count = state->unk_9E;
            ASM_KEEP(slow_count);   /* MATCH pin: retail basic-block layout depends on it */
            signed_count = slow_count;
            phase = signed_count * 0xAA;
            slow_count++;
            state->unk_9E = slow_count;
            state->unk_A0.at00.v += func_800644B8(phase) << 5;
            goto finish;
        }
        slow_count = state->unk_9E;
        ASM_KEEP(slow_count);   /* MATCH pin: retail basic-block layout depends on it */
        signed_count = slow_count;
        phase = signed_count * 0xAA;
        slow_count++;
        state->unk_9E = slow_count;
        state->unk_A0.at00.v += func_800644B8(phase) << 6;
        goto finish;
    }
    if (command_table == &D_80173DB4) {
        if (command->unk_04 == 0x100) {
            state->unk_9E = 0U;
            state->unk_A0.at00.v = 0;
        }
        if ((u32) ((u8) command->unk_04 - 1) < 4U) {
            fast_count = state->unk_9E;
            ASM_KEEP(fast_count);   /* MATCH pin: retail basic-block layout depends on it */
            signed_count = fast_count;
            phase = signed_count * 0x155;
            fast_count++;
            state->unk_9E = fast_count;
            state->unk_A0.at00.v += func_800644B8(phase, fast_count) << 5;
            goto finish;
        }
        fast_wide_count = state->unk_9E;
        ASM_KEEP(fast_wide_count);   /* MATCH pin: retail basic-block layout depends on it */
        signed_count = fast_wide_count;
        phase = signed_count * 0x155;
        fast_wide_count++;
        state->unk_9E = fast_wide_count;
        state->unk_A0.at00.v += func_800644B8(phase) << 6;
    }
finish:
    output->unk_0A = (s16) ((((S_8016F5D8_3 *)D_80175D54)->unk_A8 + state->unk_92) - state->unk_A0.at02.v);
}
