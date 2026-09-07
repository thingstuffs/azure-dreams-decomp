#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
extern M2C_UNK D_800248BC;
extern M2C_UNK D_80025238;
extern s8 D_8002745C[];

typedef struct S_8195FB34_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8195FB34_0;   /* temp_v0_3 in func_8195FB34 */

typedef struct S_8195FB34_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195FB34_1;   /* temp_v0_4 in func_8195FB34 */

typedef struct S_8195FB34_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_8195FB34_2;   /* temp_a0 in func_8195FB34 */

typedef struct S_8195FB34_3 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x46];
    s16 unk_4C;
} S_8195FB34_3;   /* temp_v1 in func_8195FB34 */

/* Clears the 8-by-8 grid and initializes an object at the given position. */
void func_8195FB34(s16 x, s16 y, s16 z) {
    s16 row_index;
    s16 column_index;
    s16 next_row;
    s16 next_column;
    s32 column_shifted;
    s8 *grid;
    s8 *row;
    void *init_object;
    void *callback;
    S_8195FB34_2 *render_state;
    void *object;
    S_8195FB34_1 *position;
    S_8195FB34_3 *object_data;

    row_index = 0;
    grid = D_8002745C;
    do {
        column_index = 0;
        row = (s8 *)(((s32) (row_index << 0x10) >> 0xC) + (u32)grid);
clear_column:
        column_shifted = column_index << 0x10;
        *(s16 *)((column_shifted >> 0xF) + (u32)row) = 0;
        next_column = column_index + 1;
        column_index = next_column;
        if (next_column < 8) {
            goto clear_column;
        }
        next_row = row_index + 1;
        row_index = next_row;
    } while (next_row < 8);
    object = func_8003FC64(0x202);
    if (object != NULL) {
        init_object = object;

        callback = &D_800248BC;

        ((S_8195FB34_0 *)object)->unk_10 = callback;
        func_8004491C(init_object, &D_80025238);
        position = ((S_8195FB34_0 *)object)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        render_state = ((S_8195FB34_0 *)object)->unk_0C;
        render_state->unk_1E = 0x2000;
        render_state->unk_1C = 0x2000;
        render_state->unk_0C = 0x808080;
        object_data = object + 0x20;
        render_state->unk_10 = 0x20;
        ((S_8195FB34_0 *)object)->unk_20 = 0xF8F82CC0;
        object_data->unk_04 = 0x13D;
        render_state->unk_08 = object_data;
        object_data->unk_4C = 0x10;
    }
}
