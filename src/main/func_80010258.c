#include "common.h"


typedef struct S_80023258_0 {
    u8 pad_00[0x80];
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
    u8 pad_90[0x114];
    void * unk_1A4;
} S_80023258_0;   /* arg0 in func_80023258 */

typedef struct S_80023258_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_1;   /* initial_node in func_80023258 */

typedef struct S_80023258_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80023258_2;   /* initial_data in func_80023258 */

typedef struct S_80023258_3 {
    u8 pad_00[0x7C];
    u8 unk_7C;
} S_80023258_3;   /* cursor1 in func_80023258 */

typedef struct S_80023258_4 {
    u8 pad_00[0x1A8];
    void * unk_1A8;
    u8 pad_1AC[0xC];
    void * unk_1B8;
    u8 pad_1BC[0xC];
    void * unk_1C8;
    u8 pad_1CC[0xC];
    void * unk_1D8;
} S_80023258_4;   /* cursor4 in func_80023258 */

typedef struct S_80023258_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_5;   /* node in func_80023258 */

typedef struct S_80023258_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_6;   /* ((S_80023258_4 *)cursor4)->unk_1C8 in func_80023258 */

typedef struct S_80023258_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_7;   /* ((S_80023258_4 *)cursor4)->unk_1D8 in func_80023258 */

typedef struct S_80023258_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_8;   /* ((S_80023258_4 *)cursor4)->unk_1A8 in func_80023258 */

typedef struct S_80023258_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023258_9;   /* ((S_80023258_4 *)cursor4)->unk_1B8 in func_80023258 */

typedef struct S_80023258_10 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_80023258_10;   /* ((S_80023258_5 *)node)->unk_04 in func_80023258 */

typedef struct S_80023258_11 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x6];
    s16 unk_08;
} S_80023258_11;   /* ((S_80023258_6 *)(((S_80023258_4 *)cursor4)->unk_1C8))->unk_04 in func_80023258 */

typedef struct S_80023258_12 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80023258_12;   /* ((S_80023258_7 *)(((S_80023258_4 *)cursor4)->unk_1D8))->unk_04 in func_80023258 */

typedef struct S_80023258_13 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80023258_13;   /* ((S_80023258_8 *)(((S_80023258_4 *)cursor4)->unk_1A8))->unk_04 in func_80023258 */

typedef struct S_80023258_14 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80023258_14;   /* ((S_80023258_9 *)(((S_80023258_4 *)cursor4)->unk_1B8))->unk_04 in func_80023258 */

/* Animate the selection marker and entry offsets, then advance the frame counter. */
s32 func_80023258(S_80023258_0 *state)
{
    s32 start_index;
    s32 index_delta;
    s32 scaled_frame;
    s32 position_delta;
    register s32 frame;
    s32 end_frame;
    s32 entry_index;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *offset_slot ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 old_offset;
    s32 next_offset;
    u8 offset;
    u8 *node_cursor;
    u8 *offset_cursor;
    void *color_node;
    S_80023258_1 *marker_node;
    S_80023258_2 *marker_data;

    start_index = state->unk_8C;
    index_delta = state->unk_88 - start_index;
    scaled_frame = state->unk_84 * 0x10;
    position_delta = (index_delta * scaled_frame) / state->unk_80;
    entry_index = 0;
    node_cursor = state;
    offset_cursor = state;
    marker_node = state->unk_1A4;
    marker_data = marker_node->unk_04;
    position_delta += 10;
    marker_data->unk_0A = start_index * 0x10 + position_delta;

loop:
    old_offset = ((S_80023258_3 *)offset_cursor)->unk_7C;
    offset_slot = offset_cursor + 0x7C;
    if (entry_index == state->unk_88) {
        s32 offset_left;
        s32 active_offset;
        register s32 offset_step;

        active_offset = old_offset;
        offset_left = 8;
        result = state->unk_80;
        frame = state->unk_84;
        offset_left -= active_offset;
        result -= frame;
        result++;
        offset_step = offset_left / result;
        next_offset = active_offset + offset_step;
    } else {
        next_offset = old_offset;
        if (next_offset != 0) {
            next_offset--;
        }
    }
    *offset_slot = next_offset;
    offset = ((S_80023258_3 *)offset_cursor)->unk_7C;

    ((S_80023258_11 *)(((S_80023258_6 *)(((S_80023258_4 *)node_cursor)->unk_1C8))->unk_04))->unk_08 =
        offset + 0x24;
    ((S_80023258_12 *)(((S_80023258_7 *)(((S_80023258_4 *)node_cursor)->unk_1D8))->unk_04))->unk_08 =
        offset + 0x8F;
    ((S_80023258_13 *)(((S_80023258_8 *)(((S_80023258_4 *)node_cursor)->unk_1A8))->unk_04))->unk_08 =
        offset + 9;
    entry_index++;
    ((S_80023258_14 *)(((S_80023258_9 *)(((S_80023258_4 *)node_cursor)->unk_1B8))->unk_04))->unk_08 =
        offset + 0x42;

    ((S_80023258_11 *)(((S_80023258_6 *)(((S_80023258_4 *)node_cursor)->unk_1C8))->unk_04))->unk_00 =
        ((S_80023258_3 *)offset_cursor)->unk_7C * 3 + 0x68;
    ((S_80023258_11 *)(((S_80023258_6 *)(((S_80023258_4 *)node_cursor)->unk_1C8))->unk_04))->unk_01 =
        ((S_80023258_3 *)offset_cursor)->unk_7C * 3 + 0x68;
    color_node = ((S_80023258_4 *)node_cursor)->unk_1C8;
    node_cursor += 4;
    ((S_80023258_10 *)(((S_80023258_5 *)color_node)->unk_04))->unk_02 =
        ((S_80023258_3 *)offset_cursor)->unk_7C * 4 + 0x60;
    offset_cursor++;
    if (entry_index < 3) {
        goto loop;
    }

    end_frame = state->unk_84;
    if (end_frame < state->unk_80) {
        result = end_frame + 1;
        state->unk_84 = result;
    } else {
        result = end_frame + 1;
    }
    return result;
}
