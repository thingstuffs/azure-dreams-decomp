#include "common.h"

typedef struct S_80056654_0 {
    u16 unk_00;
    u8 pad_02[0x4];
    u16 unk_06;
    u8 pad_08[0x4];
    u16 unk_0C;
    u8 pad_0E[0x14];
    u8 unk_22;
    u8 unk_23;
    u8 pad_24[0xC];
    s32 unk_30;
    u8 pad_34[0x8];
    union { u16 u16; s32 s32; } unk_3C;   /* accessed as both */
    u8 pad_40[0xC];
    s32 unk_4C;
    u8 pad_50[0x20];
    s32 unk_70;
} S_80056654_0;   /* arg0 in func_80056654 */

typedef struct S_80056654_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
    u8 pad_20[0x1A];
    u16 unk_3A;
    u8 pad_3C[0x14];
    s16 unk_50;
    u16 unk_52;
} S_80056654_1;   /* temp_a2 in func_80056654 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s32 field0;
    s32 field4;
    u8 pad8[0x16 - 8];
    s16 field16;
    s16 field18;
    u8 pad1A[0x40 - 0x1A];
} S_80084918;

s32 func_800565D8(void *, s32, void *);
s32 func_8005EB78(s32);
void func_8005F134(S_80084918 *);
extern s32 D_80073740[];
extern S_80084918 D_80084918;
extern u8 D_80084960[];

/* Updates voice pitch parameters and clears a completed pitch adjustment. */
void func_80056654(S_80056654_0 *state, s32 force_update) {
    s32 pitch_offset;
    s32 packed_pitch;
    s32 pitch_adjustment;
    S_80056654_1 *channel;
    s32 base_pitch;
    s32 coarse_pitch;
    s32 *voice_entry;
    s32 *voice_table;
    channel = D_80084960 + (state->unk_06 * 0x9C);
    if ((state->unk_4C != 0) || (state->unk_30 != 0) ||
        (channel->unk_08 != 0) || (channel->unk_50 != 0) ||
        (channel->unk_1C != state->unk_70) || (force_update != 0)) {
        state->unk_70 = (s32) channel->unk_1C;
        pitch_offset = state->unk_3C.u16 + (channel->unk_3A + channel->unk_52);
        pitch_adjustment = func_800565D8(state, channel->unk_1C, channel);
        voice_table = D_80073740;
        base_pitch = (state->unk_0C << 7) + pitch_adjustment;
        D_80084918.field4 = 0x60;
        voice_entry = voice_table + state->unk_00;
        ASM_KEEP_NV(voice_entry);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        packed_pitch = pitch_offset + base_pitch;
        coarse_pitch = (s32) (packed_pitch << 0x10) >> 0x17;
        packed_pitch &= 0x7F;
        D_80084918.field0 = *voice_entry;
        coarse_pitch <<= 8;
        packed_pitch |= coarse_pitch;
        if (state->unk_23 != 0) {
            D_80084918.field18 = (s16) (((state->unk_22 - 1) << 8) | (0x7F - state->unk_23));
        } else {
            D_80084918.field18 = (s16) (state->unk_23 | (state->unk_22 << 8));
        }
        D_80084918.field16 = (s16) packed_pitch;
        func_8005F134(&D_80084918);
    }
    if ((state->unk_30 != 0) && (func_8005EB78(D_80073740[state->unk_00]) == 0)) {
        state->unk_30 = 0;
        state->unk_3C.s32 = 0;
    }
}
