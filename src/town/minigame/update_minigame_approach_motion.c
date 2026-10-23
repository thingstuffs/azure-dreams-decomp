#include "common.h"
#include "shared/entity.h"
#include "shared/object_flags.h"

typedef struct S_800220A8_0 {
    s16 unk_00;
    u16 unk_02;
    void * unk_04;
} S_800220A8_0;   /* arg0 in update_minigame_approach_motion */


typedef struct S_800220A8_2 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800220A8_2;   /* ((S_800220A8_0 *)arg0)->unk_04 in update_minigame_approach_motion */


s32 rsin(s32);

/* Update motion through approach, oscillation, and withdrawal, flagging completion. */
void update_minigame_approach_motion(void *motion_state, void *motion) {
    s16 state;

    if (((S_800220A8_2 *)(((S_800220A8_0 *)motion_state)->unk_04))->unk_18 == 2) {
        ((S_800220A8_0 *)motion_state)->unk_00 = 3;
    }
    state = ((S_800220A8_0 *)motion_state)->unk_00;
    switch (state) {
    case 0:
        if ((((ObjectPosition *)motion)->z.v += 0x100000) < (s32)0xFF900000) {
            return;
        }
        ((S_800220A8_0 *)motion_state)->unk_02 = 0;
        ((ObjectPosition *)motion)->velocity_z = -0x40000;
        ((S_800220A8_0 *)motion_state)->unk_00 = 1;
        return;
    case 1:
        ((ObjectPosition *)motion)->z.v += ((ObjectPosition *)motion)->velocity_z;
        ((ObjectPosition *)motion)->velocity_z += 0x4000;
        if (((ObjectPosition *)motion)->velocity_z != 0x40000) {
            return;
        }
        ((S_800220A8_0 *)motion_state)->unk_00 = 2;
        return;
    case 2:
        ((ObjectPosition *)motion)->z.v += ((ObjectPosition *)motion)->velocity_z;
        ((ObjectPosition *)motion)->velocity_z -= 0x8000;
        if (((ObjectPosition *)motion)->velocity_z != -0x40000) {
            return;
        }
        ((S_800220A8_0 *)motion_state)->unk_00 = 1;
        return;
    case 0xF0: {
        u16 phase;
        s32 position;
        phase = (((S_800220A8_0 *)motion_state)->unk_02 + 1) & 0x7F;
        ((S_800220A8_0 *)motion_state)->unk_02 = phase;
        ((ObjectPosition *)motion)->z.v = (rsin(phase << 6) << 7) - 0x700000;
        return;
    }
    case 3: {
        s32 position;
        position = ((ObjectPosition *)motion)->z.v;
        position += (s32)0xFFF00000;
        ((ObjectPosition *)motion)->z.v = position;
        if ((s32)0xFE000000 < position) {
            return;
        }
        (*(u16 *)((u8 *)motion_state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    }
}
