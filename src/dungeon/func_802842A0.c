#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_800C7B38;

typedef struct S_800172A0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800172A0_0;   /* arg0 in func_800172A0 */

typedef struct S_800172A0_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800172A0_2;   /* temp_s5 in func_800172A0 */

typedef struct S_800172A0_3 {
    void * unk_00;
    u8 pad_04[0x8];
    void * unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x8];
    s16 unk_24;
    s16 unk_26;
} S_800172A0_3;   /* temp_s1 in func_800172A0 */

/* Initialize a bounded random position and its associated effect state. */
void func_800172A0(S_800172A0_0 *source, s16 base_offset) {
    s16 state_offset;
    s16 position_x;
    s16 position_y;
    GameView *state;
    void *effect;
    s32 random_angle;
    S_800172A0_2 *bounds;
    s16 rotation_step;
    s32 random_bits;

    state = &gameWork.view;
    bounds = (u8 *)state + 0x1C4;
    effect = (u8 *)state + 0xB8;
    random_angle = (rand() & 0x1FFF) - 0x1000;
    if (!((u16) *((s16 *)&D_80013714) & 2)) {
        position_x = source->unk_02 + (func_80064584(random_angle) * 2);
        state->unk_0A4 = position_x;
        if (position_x < 0) {
            state->unk_0A4 = 0;
        } else if (position_x >= bounds->unk_1C) {
            state->unk_0A4 = (s16) ((u16) bounds->unk_1C - 1);
        }
        position_y = source->unk_06 + (func_800644B8(random_angle) * 2);
        state->unk_0A6 = position_y;
        if (position_y < 0) {
            state->unk_0A6 = 0;
        } else if (position_y >= bounds->unk_1E) {
            state->unk_0A6 = (s16) ((u16) bounds->unk_1E - 1);
        }
        state_offset = (s16) (source->unk_0A - 0x400);
        state->unk_0AC = 0;
        state->unk_0A8 = state_offset;
        random_bits = rand();
        rotation_step = -0x800;
        if (random_bits & 1) {
            rotation_step = 0x800;
        }
        state->viewAngle = rotation_step;
        ((S_800172A0_3 *)effect)->unk_00 = (void *) (effect + 4);
        ((S_800172A0_3 *)effect)->unk_14 = 1;
        ((S_800172A0_3 *)effect)->unk_24 = 0x40;
        ((S_800172A0_3 *)effect)->unk_0C = source;
        ((S_800172A0_3 *)effect)->unk_18 = 0;
        ((S_800172A0_3 *)effect)->unk_26 = base_offset;
        state->slot[0].callback = &D_800C7B38;
        state_offset = base_offset + ((((S_800172A0_3 *)effect)->unk_24 + 1) * 0x30);
        state->unk_098 = state_offset;
        ((S_800172A0_3 *)effect)->unk_10 = (s32) state_offset;
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) + 1);
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
