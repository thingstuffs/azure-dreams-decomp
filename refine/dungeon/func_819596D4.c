#include "common.h"
#include "m2c_compat.h"

extern s16 D_80083780[];
extern u8 D_80083498[];
extern u8 D_800DF334[];
M2C_UNK func_80024654();
void *func_8003FD64();
s32 func_800644B8();
s32 func_80064584();
s16 func_800A07D0();
M2C_UNK func_800B835C();
extern M2C_UNK D_80028214;
extern M2C_UNK D_80024728;

typedef struct S_80024ED4_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024ED4_0;   /* arg0 in func_80024ED4 */

typedef struct S_80024ED4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80024ED4_1;   /* temp_v0 in func_80024ED4 */

typedef struct S_80024ED4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80024ED4_2;   /* temp_s0 in func_80024ED4 */

typedef struct S_80024ED4_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_80024ED4_3;   /* temp_v1 in func_80024ED4 */

typedef struct S_80024ED4_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x16];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
} S_80024ED4_4;   /* temp_s1 in func_80024ED4 */

/* Creates up to sixteen linked effect segments at the given position. */
void *func_80024ED4(S_80024ED4_0 *position) {
    s32 setup_params[2];
    s32 segment_index;
    M2C_UNK alloc_flags;
    s16 angle;
    u16 x;
    u16 y;
    u16 z;
    u8 *parent;
    S_80024ED4_2 *coords;
    S_80024ED4_4 *segment_state;
    void *segment;
    S_80024ED4_3 *render_state;
    void *previous_segment;
    s16 *origin_coords;

    origin_coords = D_80083780;
    previous_segment = NULL;
    segment_index = 0;
    angle = func_800A07D0(origin_coords[1], origin_coords[3], position->unk_02, position->unk_06);
    do {
        alloc_flags = 0x12;
        if (segment_index != 0) {
            alloc_flags = 0x212;
        }
        parent = previous_segment;
        if (previous_segment == NULL) {
            parent = D_80083498;
        }
        segment = func_8003FD64(alloc_flags, parent);
        segment_state = segment + 0x20;
        if (segment != NULL) {
            coords = ((S_80024ED4_1 *)segment)->unk_08;
            ((S_80024ED4_1 *)segment)->unk_10 = &D_80024728;
            x = (u16) position->unk_02;
            coords->unk_02 = x;
            coords->unk_0E = x;
            y = (u16) position->unk_06;
            coords->unk_06 = y;
            coords->unk_12 = y;
            z = position->unk_0A;
            coords->unk_0A = z;
            coords->unk_16 = z;
            render_state = ((S_80024ED4_1 *)segment)->unk_0C;
            render_state->unk_08 = &D_80028214;
            render_state->unk_1E = 0x800;
            render_state->unk_1C = 0x800;
            segment_state->unk_30 = 0x10;
            if (segment_index == 0) {
                segment_state->unk_14 = (s16) (coords->unk_02 + (func_80064584(angle) >> 5));
                segment_state->unk_16 = (s16) (coords->unk_06 + (func_800644B8(angle) >> 5));
                segment_state->unk_18 = (s16) (coords->unk_0A - 0x40);
                func_80024654((s16) coords->unk_02, (s16) coords->unk_06, (s16) coords->unk_0A, segment_state->unk_14, (s32) segment_state->unk_16, (s32) segment_state->unk_18, segment + 0x2C);
                setup_params[0] = 0x01200340;
                setup_params[1] = 0x200020;
                func_800B835C(D_800DF334, setup_params, 1, 0);
            }
            segment_state->unk_08 = previous_segment;
            previous_segment = segment;
            segment_state->unk_38 = segment_index;
        } else {
            return previous_segment;
        }
        segment_index++;
    } while (segment_index < 0x10);
    return segment;
}
