/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017EB8_1 {
    u8 pad_00[0x24];
    void * unk_24;
} S_80017EB8_1;   /* D_80016000[0] in func_80017EB8 */

typedef struct S_80017EB8_2 {
    u8 pad_00[0x6C];
    s32 unk_6C;
} S_80017EB8_2;   /* ((S_80017EB8_1 *)(D_80016000[0]))->unk_24 in func_80017EB8 */

typedef struct S_80017EB8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80017EB8_3;   /* ((temp_a1 * 0x14) + ((S_80017EB8_2 *)(((S_80017EB8_1 *)(D_80016000[0]))->unk_24))->unk_6C) in func_80017EB8 */

typedef struct S_80017EB8_4 {
    s16 unk_00;
} S_80017EB8_4;   /* (temp_a0 * 0x14) + ((S_80017EB8_3 *)(((temp_a1 * 0x14) + ((S_80017EB8_2 *)(((S_80017EB8_1 *)(D_80016000[0]))->unk_24))->unk_6C)))->unk_0C in func_80017EB8 */






extern s32 func_800186D8();
extern void *D_80016000[3];

typedef struct S_80017EB8_0 {
    u8 unk_00;
    u8 unk_01;
} S_80017EB8_0;   /* arg0 in func_80017EB8 */

s32 func_80017EB8(S_80017EB8_0 *arg0) {
    s32 temp_s0;
    s32 var_v0;
    register s32 var_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 temp_a0;
    u8 temp_a1;

    temp_a1 = arg0->unk_01;
    temp_a0 = arg0->unk_00;
    temp_s0 = ((S_80017EB8_4 *)((temp_a0 * 0x14) + ((S_80017EB8_3 *)(((temp_a1 * 0x14) + ((S_80017EB8_2 *)(((S_80017EB8_1 *)(D_80016000[0]))->unk_24))->unk_6C)))->unk_0C))->unk_00;
    if (func_800186D8(temp_a0, temp_a1) != 0) {
        goto zero;
    }
    var_v0 = 0;
    var_v1 = temp_s0 - 8;
    if ((u32) var_v1 < 2U) {
        var_v0 = 1;
        goto done;
    }
zero:
    var_v0 = 0;
done:
    return var_v0;
}
