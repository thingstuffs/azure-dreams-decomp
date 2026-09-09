#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8006658C();                 /* extern */
M2C_UNK func_800666F4();                      /* extern */

typedef struct S_800B0BE0_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    u8 pad_10[0x4];
    s8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x4];
    u8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x6];
    s8 unk_24;
    s8 unk_25;
} S_800B0BE0_0;   /* arg3 in func_800B0BE0 */

typedef struct S_800B0BE0_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
} S_800B0BE0_1;   /* arg1 in func_800B0BE0 */

typedef struct S_800B0BE0_2 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
} S_800B0BE0_2;   /* *arg2 in func_800B0BE0 */

typedef struct S_800B0BE0_3 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800B0BE0_3;   /* temp_v1 in func_800B0BE0 */

typedef struct S_800B0BE0_4 {
    u8 pad_00[0x9];
    u8 unk_09;
    u8 pad_0A[0x1];
    u8 unk_0B;
} S_800B0BE0_4;   /* temp_v1_2 in func_800B0BE0 */

typedef struct S_800B0BE0_5 {
    s8 unk_00;
} S_800B0BE0_5;   /* temp_v1_3 in func_800B0BE0 */

/* Fill and submit a textured quad, then advance the primitive and texture cursors. */
void *func_800B0BE0(s32 draw_context, S_800B0BE0_1 *draw_settings, void **texture_cursor, void *primitive) {
    s32 submit_context;
    u32 texture_page;
    s8 u_end;
    s8 v_end;
    u8 u_start;
    u8 v_start;
    S_800B0BE0_3 *u_bounds;
    S_800B0BE0_4 *v_bounds;
    void *texture_entry;
    u16 page_override;

    ((S_800B0BE0_0 *)primitive)->unk_04 = (s32) draw_settings->unk_0C;
    func_800666F4(primitive);
    ((S_800B0BE0_0 *)primitive)->unk_0E = (u16) ((S_800B0BE0_2 *)(*texture_cursor))->unk_06;
    page_override = draw_settings->unk_10;
    if (page_override != 0) {
        texture_page = page_override + (((S_800B0BE0_2 *)(*texture_cursor))->unk_04 & 0xFF9F);
    } else {
        texture_page = ((S_800B0BE0_2 *)(*texture_cursor))->unk_04;
    }
    ((S_800B0BE0_0 *)primitive)->unk_16 = (u16) texture_page;
    u_start = ((S_800B0BE0_2 *)(*texture_cursor))->unk_08;
    ((S_800B0BE0_0 *)primitive)->unk_1C = u_start;
    ((S_800B0BE0_0 *)primitive)->unk_0C = u_start;
    u_bounds = *texture_cursor;
    u_end = (u_bounds->unk_08 + u_bounds->unk_0A) - 1;
    ((S_800B0BE0_0 *)primitive)->unk_24 = u_end;
    ((S_800B0BE0_0 *)primitive)->unk_14 = u_end;
    v_start = ((S_800B0BE0_2 *)(*texture_cursor))->unk_09;
    ((S_800B0BE0_0 *)primitive)->unk_15 = v_start;
    ((S_800B0BE0_0 *)primitive)->unk_0D = v_start;
    v_bounds = *texture_cursor;
    submit_context = draw_context;

    v_end = (v_bounds->unk_09 + v_bounds->unk_0B) - 1;
    ((S_800B0BE0_0 *)primitive)->unk_25 = v_end;
    ((S_800B0BE0_0 *)primitive)->unk_1D = v_end;
    func_8006658C(submit_context, primitive);
    texture_entry = *texture_cursor;
    primitive += 0x28;
    if (((S_800B0BE0_5 *)texture_entry)->unk_00 < 0) {
        *texture_cursor = NULL;
    } else {
        *texture_cursor = texture_entry + 0xC;
    }
    return primitive;
}
