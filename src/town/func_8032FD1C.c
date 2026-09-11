/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A51C_3 {
    u8 pad_00[0x24];
    void * unk_24;
} S_8001A51C_3;   /* D_80016000[0] in func_8001A51C */

typedef struct S_8001A51C_4 {
    u8 pad_00[0x70];
    void * unk_70;
} S_8001A51C_4;   /* ((S_8001A51C_3 *)(D_80016000[0]))->unk_24 in func_8001A51C */






extern void *D_80016000[3];

typedef struct S_8001A51C_0 {
    u8 pad_00[0x1DC];
    u16 * unk_1DC;
} S_8001A51C_0;   /* temp_v0 in func_8001A51C */

typedef struct S_8001A51C_1 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} S_8001A51C_1;   /* arg1 in func_8001A51C */

typedef struct S_8001A51C_2 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_8001A51C_2;   /* var_t2 in func_8001A51C */

/* Copy nonzero 16-bit values from the source into the destination rectangle. */
void func_8001A51C(u16 *source, S_8001A51C_1 *rect) {
    s32 col;
    s32 row;
    register s32 dst_index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 row_offset;
    s32 stride_shift;
    volatile u16 *src_cursor;
    u16 *dst_base;
    register u16 *dst_cell ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s8 *grid_info;
    void *buffer_state;

    src_cursor = source;
    ASM_KEEP(src_cursor);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    buffer_state = ((S_8001A51C_4 *)(((S_8001A51C_3 *)(D_80016000[0]))->unk_24))->unk_70;
    grid_info = (s8 *)buffer_state + 0x1DC;
    dst_base = ((S_8001A51C_0 *)buffer_state)->unk_1DC;
    row = 0;
    if (rect->unk_06 > 0) {
        do {
            col = 0;
            if (rect->unk_04 > 0) {
                do {
                    dst_index = rect->unk_00;
                    dst_index += col;
                    do {
                        row_offset = rect->unk_02;
                    } while (0);
                    row_offset += row;
                    stride_shift = ((S_8001A51C_2 *)grid_info)->unk_14;
                    row_offset <<= stride_shift;
                    dst_index += row_offset;
                    if (*src_cursor != 0) {
                        dst_cell = (u16 *)((dst_index << 1) + (s32)dst_base);
                        ASM_KEEP(dst_cell);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        *dst_cell = *src_cursor;
                    }
                    col += 1;
                    src_cursor += 1;
                } while (col < rect->unk_04);
            }
            do {
                row += 1;
            } while (0);
        } while (row < rect->unk_06);
    }
}
