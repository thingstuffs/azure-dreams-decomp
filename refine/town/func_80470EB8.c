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

/* Checks whether the selected entry is 8 or 9 and func_800186D8 returns zero. */
s32 func_80017EB8(S_80017EB8_0 *position) {
    s32 entry_value;
    s32 matches;
    register s32 value_offset ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u8 column;
    u8 row;

    row = position->unk_01;
    column = position->unk_00;
    entry_value = ((S_80017EB8_4 *)((column * 0x14) + ((S_80017EB8_3 *)(((row * 0x14) + ((S_80017EB8_2 *)(((S_80017EB8_1 *)(D_80016000[0]))->unk_24))->unk_6C)))->unk_0C))->unk_00;
    if (func_800186D8(column, row) != 0) {
        goto zero;
    }
    matches = 0;
    value_offset = entry_value - 8;
    if ((u32) value_offset < 2U) {
        matches = 1;
        goto done;
    }
zero:
    matches = 0;
done:
    return matches;
}
