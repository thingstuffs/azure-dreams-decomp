#include "common.h"

typedef struct S_8001E824_0 {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
    s8 unk_03;
} S_8001E824_0;   /* entity in func_8001E824 */

s32 func_800A6D30();

void func_8001E824(void *arg0) {
    u8 *entity = arg0;
    s16 var_s0;
    s16 var_s1;
    s16 var_s2;
    s32 minus_128;
    s32 temp_v0_2;
    u8 temp_v0;

    var_s0 = 0;
    temp_v0 = ((S_8001E824_0 *)entity)->unk_01;
    var_s2 = var_s0;
    switch (temp_v0) {
    case 4:
        var_s2 = 1;
        if (((S_8001E824_0 *)entity)->unk_00 != 0x11) {
            var_s2 = (func_800A6D30() & 7) | 4;
        }
        var_s0 = -0x80;
        break;
    case 15:
        if (((S_8001E824_0 *)entity)->unk_00 == 9) {
            var_s0 |= 0x40;
        }
    case 17:
        if (!(func_800A6D30() & 3)) {
            temp_v0_2 = (func_800A6D30() & 3) - 1;
            var_s2 = temp_v0_2;
            if (temp_v0_2 < 0) {
                var_s0 |= 0x40;
            }
        }
    case 16:
        minus_128 = -0x80;
        var_s1 = var_s0 | minus_128;
        var_s0 = var_s1;
        if (func_800A6D30() & 7) {
            break;
        }
        var_s2 = -1;
        var_s0 = var_s1 | 0x40;
        break;
    case 18:
        var_s2 = ((u32)(func_800A6D30() & 0xFFFF) % 40U) + 0x3C;
        break;
    case 1:
    default:
        break;
    }
    ((S_8001E824_0 *)entity)->unk_02 = var_s2;
    ((S_8001E824_0 *)entity)->unk_03 = var_s0;
}
