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
    s32 dst_index;
    u16 *dst_base;
    s8 *grid_info;
    void *buffer_state;
    volatile u16 *src_cursor;

    src_cursor = source;
    buffer_state = ((S_8001A51C_4 *)(((S_8001A51C_3 *)(D_80016000[0]))->unk_24))->unk_70;
    grid_info = (s8 *)buffer_state + 0x1DC;
    dst_base = ((S_8001A51C_0 *)buffer_state)->unk_1DC;
    for (row = 0; row < rect->unk_06; row++) {
        for (col = 0; col < rect->unk_04; col++) {
            dst_index = rect->unk_00 + col + ((rect->unk_02 + row) << ((S_8001A51C_2 *)grid_info)->unk_14);
            if (*src_cursor != 0) {
                dst_base[dst_index] = *src_cursor;
            }
            src_cursor++;
        }
    }
}
