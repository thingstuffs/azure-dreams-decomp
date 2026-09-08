#include "common.h"
#include "records/Rec_func_800AB030_arg0.h"


extern s32 func_800AAE98(void *);
extern void func_800AAFE0(void *, s32);
extern s32 func_800AB030(void *);
extern u8 D_800AB408[];
extern u8 D_800AB708[];



typedef struct S_800AB5C0_1 {
    u8 pad_00[0x2];
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800AB5C0_1;   /* arg1 in func_800AB5C0 */

/* Smooth coordinates toward the adjusted sample, snapping to it when the timer expires. */
void func_800AB5C0(Rec_func_800AB030_arg0 *state, S_800AB5C0_1 *coords) {
    s16 sampled_coords[12];
    s32 z_offset;
    u16 ticks_left;

    if (state->unk_90 < 100) {
        state->unk_50 = D_800AB708;
    }
    func_800AAFE0(sampled_coords, 4);
    z_offset = func_800AAE98(coords);
    sampled_coords[5] -= z_offset + func_800AB030(state);
    ticks_left = state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if ((s16)ticks_left < 0) {
        coords->unk_0E = coords->unk_02.u = sampled_coords[1];
        coords->unk_12 = coords->unk_06.u = sampled_coords[3];
        coords->unk_16 = coords->unk_0A.u = sampled_coords[5];
        state->unk_50 = D_800AB408;
        state->unk_6C = 150;
        return;
    }
    coords->unk_02.s = (coords->unk_02.s + sampled_coords[1]) / 2;
    coords->unk_06.s = (coords->unk_06.s + sampled_coords[3]) / 2;
    coords->unk_0A.s = (coords->unk_0A.s + sampled_coords[5]) / 2;
}
