#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_800220A8_0 {
    s16 unk_00;
    u16 unk_02;
    void * unk_04;
} S_800220A8_0;   /* arg0 in func_800220A8 */

typedef struct S_800220A8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800220A8_1;   /* arg1 in func_800220A8 */

typedef struct S_800220A8_2 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800220A8_2;   /* ((S_800220A8_0 *)arg0)->unk_04 in func_800220A8 */


M2C_UNK func_800644B8();

/* Update motion through approach, oscillation, and withdrawal, flagging completion. */
void func_800220A8(void *motion_state, void *motion) {
    s16 state;

    if (((S_800220A8_2 *)(((S_800220A8_0 *)motion_state)->unk_04))->unk_18 == 2) {
        ((S_800220A8_0 *)motion_state)->unk_00 = 3;
    }
    state = ((S_800220A8_0 *)motion_state)->unk_00;
    switch (state) {
    case 0:
        if ((((S_800220A8_1 *)motion)->unk_08 += 0x100000) < (s32)0xFF900000) {
            return;
        }
        ((S_800220A8_0 *)motion_state)->unk_02 = 0;
        ((S_800220A8_1 *)motion)->unk_14 = -0x40000;
        ((S_800220A8_0 *)motion_state)->unk_00 = 1;
        return;
    case 1:
        ((S_800220A8_1 *)motion)->unk_08 += ((S_800220A8_1 *)motion)->unk_14;
        ((S_800220A8_1 *)motion)->unk_14 += 0x4000;
        if (((S_800220A8_1 *)motion)->unk_14 != 0x40000) {
            return;
        }
        ((S_800220A8_0 *)motion_state)->unk_00 = 2;
        return;
    case 2:
        ((S_800220A8_1 *)motion)->unk_08 += ((S_800220A8_1 *)motion)->unk_14;
        ((S_800220A8_1 *)motion)->unk_14 -= 0x8000;
        if (((S_800220A8_1 *)motion)->unk_14 != -0x40000) {
            return;
        }
        ((S_800220A8_0 *)motion_state)->unk_00 = 1;
        return;
    case 0xF0: {
        u16 phase;
        s32 position;
        phase = (((S_800220A8_0 *)motion_state)->unk_02 + 1) & 0x7F;
        ((S_800220A8_0 *)motion_state)->unk_02 = phase;
        ((S_800220A8_1 *)motion)->unk_08 = (func_800644B8(phase << 6) << 7) - 0x700000;
        return;
    }
    case 3: {
        s32 position;
        position = ((S_800220A8_1 *)motion)->unk_08;
        position += (s32)0xFFF00000;
        ((S_800220A8_1 *)motion)->unk_08 = position;
        if ((s32)0xFE000000 < position) {
            return;
        }
        (*(u16 *)((u8 *)motion_state + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
    }
}
