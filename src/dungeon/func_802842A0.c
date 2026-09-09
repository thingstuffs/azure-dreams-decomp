#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern volatile s16 D_80013714[8];
extern s32 D_80083460[3];
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

typedef struct S_800172A0_1 {
    u8 pad_00[0x98];
    s16 unk_98;
    u8 pad_9A[0xA];
    s16 unk_A4;
    s16 unk_A6;
    s16 unk_A8;
    u8 pad_AA[0x2];
    s16 unk_AC;
    u8 pad_AE[0x2];
    s16 unk_B0;
    u8 pad_B2[0x2];
    M2C_UNK * unk_B4;
} S_800172A0_1;   /* state in func_800172A0 */

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

typedef struct S_800172A0_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800172A0_4;   /* counter in func_800172A0 */

/* Initialize a bounded random position and its associated effect state. */
void func_800172A0(S_800172A0_0 *source, s16 base_offset) {
    s16 state_offset;
    s16 position_x;
    s16 position_y;
    u8 *state;
    void *effect;
    s32 random_angle;
    S_800172A0_2 *bounds;
    u16 *counter;
    s16 rotation_step;
    s32 random_bits;

    state = (u8 *)&D_80083178;
    bounds = state + 0x1C4;
    effect = state + 0xB8;
    random_angle = (rand() & 0x1FFF) - 0x1000;
    if (!((u16) *D_80013714 & 2)) {
        position_x = source->unk_02 + (func_80064584(random_angle) * 2);
        ((S_800172A0_1 *)state)->unk_A4 = position_x;
        if (position_x < 0) {
            ((S_800172A0_1 *)state)->unk_A4 = 0;
        } else if (position_x >= bounds->unk_1C) {
            ((S_800172A0_1 *)state)->unk_A4 = (s16) ((u16) bounds->unk_1C - 1);
        }
        position_y = source->unk_06 + (func_800644B8(random_angle) * 2);
        ((S_800172A0_1 *)state)->unk_A6 = position_y;
        if (position_y < 0) {
            ((S_800172A0_1 *)state)->unk_A6 = 0;
        } else if (position_y >= bounds->unk_1E) {
            ((S_800172A0_1 *)state)->unk_A6 = (s16) ((u16) bounds->unk_1E - 1);
        }
        state_offset = (s16) (source->unk_0A - 0x400);
        ((S_800172A0_1 *)state)->unk_AC = 0;
        ((S_800172A0_1 *)state)->unk_A8 = state_offset;
        random_bits = rand();
        rotation_step = -0x800;
        if (random_bits & 1) {
            rotation_step = 0x800;
        }
        ((S_800172A0_1 *)state)->unk_B0 = rotation_step;
        ((S_800172A0_3 *)effect)->unk_00 = (void *) (effect + 4);
        ((S_800172A0_3 *)effect)->unk_14 = 1;
        ((S_800172A0_3 *)effect)->unk_24 = 0x40;
        ((S_800172A0_3 *)effect)->unk_0C = source;
        ((S_800172A0_3 *)effect)->unk_18 = 0;
        ((S_800172A0_3 *)effect)->unk_26 = base_offset;
        ((S_800172A0_1 *)state)->unk_B4 = &D_800C7B38;
        state_offset = base_offset + ((((S_800172A0_3 *)effect)->unk_24 + 1) * 0x30);
        ((S_800172A0_1 *)state)->unk_98 = state_offset;
        ((S_800172A0_3 *)effect)->unk_10 = (s32) state_offset;
        counter = (u16 *)D_80083460;
        ((S_800172A0_4 *)counter)->unk_0A = (u16) (((S_800172A0_4 *)counter)->unk_0A + 1);
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
