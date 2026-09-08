#include "common.h"
#include "m2c_compat.h"

extern u8 D_80083160[];

typedef struct S_8009D808_0 {
    u16 unk_00;
    u16 unk_02;
} S_8009D808_0;   /* arg0 in func_8009D808 */

typedef struct S_8009D808_1 {
    u16 unk_00;
    u16 unk_02;
} S_8009D808_1;   /* arg2 in func_8009D808 */

typedef struct S_8009D808_2 {
    u16 unk_00;
    u16 unk_02;
} S_8009D808_2;   /* arg1 in func_8009D808 */

typedef struct S_8009D808_3 {
    s16 unk_00;
    s16 unk_02;
} S_8009D808_3;   /* var_t0 in func_8009D808 */

/* Compute coordinate bounds for four points using the configured limits. */
void func_8009D808(void *points, S_8009D808_2 *max_point, S_8009D808_1 *min_point) {
    s16 x_for_max;
    s16 x_for_min;
    s16 y_for_max;
    s16 y_for_min;
    s32 x_limit;
    s32 y_limit;
    u16 first_x;
    u16 first_y;
    s32 base_extent;
    u8 *config_base;
    u8 *size_config;
    void *point;

    first_x = ((S_8009D808_0 *)points)->unk_00;
    min_point->unk_00 = first_x;
    max_point->unk_00 = first_x;
    first_y = ((S_8009D808_0 *)points)->unk_02;
    min_point->unk_02 = first_y;
    max_point->unk_02 = first_y;
    config_base = D_80083160;
    size_config = config_base + 0x1DC;
    if ((s16) max_point->unk_00 < 0) {
        min_point->unk_00 = 0U;
        max_point->unk_00 = 0U;
    }
    if ((s16) max_point->unk_02 < 0) {
        min_point->unk_02 = 0U;
        max_point->unk_02 = 0U;
    }
    base_extent = 0x40;
    point = points;
    do {
        x_for_max = ((S_8009D808_3 *)point)->unk_00;
        if ((s16) max_point->unk_00 < x_for_max) {
            max_point->unk_00 = (u16) ((S_8009D808_3 *)point)->unk_00;
            x_limit = (base_extent << ((s16 *)size_config)[0xA]) - 1;
            if (x_limit < x_for_max) {
                max_point->unk_00 = (u16) x_limit;
            }
        }
        x_for_min = ((S_8009D808_3 *)point)->unk_00;
        if ((s16) min_point->unk_00 > x_for_min) {
            min_point->unk_00 = (u16) ((S_8009D808_3 *)point)->unk_00;
            if (x_for_min < 0) {
                min_point->unk_00 = 0U;
            }
        }
        y_for_max = ((S_8009D808_3 *)point)->unk_02;
        if ((s16) max_point->unk_02 < y_for_max) {
            max_point->unk_02 = (u16) ((S_8009D808_3 *)point)->unk_02;
            y_limit = (base_extent << ((s16 *)size_config)[0xB]) - 1;
            if (y_limit < y_for_max) {
                max_point->unk_02 = (u16) y_limit;
            }
        }
        y_for_min = ((S_8009D808_3 *)point)->unk_02;
        if ((s16) min_point->unk_02 > y_for_min) {
            min_point->unk_02 = (u16) ((S_8009D808_3 *)point)->unk_02;
            if (y_for_min < 0) {
                min_point->unk_02 = 0U;
            }
        }
        point += 8;
    } while ((s32) point < (s32) (points + 0x20));
}
