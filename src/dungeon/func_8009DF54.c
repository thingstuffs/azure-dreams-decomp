#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A36B4_0 {
    void * unk_00;
    u8 pad_04[0x3A];
    u16 unk_3E;
    u8 pad_40[0x5C];
    u16 unk_9C;
} S_800A36B4_0;   /* arg0 in func_800A36B4; pointer addresses record offset 0x14 */

typedef struct S_800A36B4_1 {
    void * unk_00;
} S_800A36B4_1;   /* arg1 in func_800A36B4; pointer addresses record offset 0x14 */

typedef struct S_800A36B4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A36B4_2;   /* temp_a3 in func_800A36B4 */

typedef struct S_800A36B4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A36B4_3;   /* temp_s3 in func_800A36B4 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 func_800A44E0(u16, u16, s16, s16);
extern s32 func_800BCB04(s32, s32, s16);

/* Checks whether the tile path from source to target is clear. */
s32 func_800A36B4(void *source, void *target) {
    s32 step_y;
    s32 step_x;
    S_800A36B4_2 *source_pos;
    S_800A36B4_3 *target_pos;
    s32 check_param;
    s32 tile_x;
    s32 tile_y;
    s32 height;
    s16 check_height;

    source_pos = ((S_800A36B4_0 *)((u8 *)source - 0x14))->unk_00;
    target_pos = ((S_800A36B4_1 *)((u8 *)target - 0x14))->unk_00;
    step_x = source_pos->unk_24 - target_pos->unk_24;
    check_param = ((S_800A36B4_0 *)((u8 *)source - 0x14))->unk_3E;
    if (step_x != 0) {
        if (step_x > 0) {
            step_x = 1;
        } else {
            step_x = -1;
        }
    }
    step_y = source_pos->unk_25 - target_pos->unk_25;
    if (step_y != 0) {
        if (step_y > 0) {
            step_y = 1;
        } else {
            step_y = -1;
        }
    }
    tile_x = source_pos->unk_24;
    tile_y = source_pos->unk_25;
    height = ((S_800A36B4_0 *)((u8 *)source - 0x14))->unk_9C;

    while (tile_x != target_pos->unk_24 ||
           tile_y != target_pos->unk_25) {
        check_height = height;
        if ((func_800A44E0((tile_x << 6) & 0xFFC0,
                           (tile_y << 6) & 0xFFC0,
                           check_height, check_param) << 16) != 0) {
            return 0;
        }
        tile_x -= step_x;
        tile_y -= step_y;
        {
            s32 next_height;
            next_height = func_800BCB04(((tile_x << 6) + 0x20) & 0xFFE0,
                                     ((tile_y << 6) + 0x20) & 0xFFE0,
                                     height - 0x20);
            if ((s16)next_height < check_height) {
                height = next_height;
            }
        }
    }
    return 1;
}
