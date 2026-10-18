/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"

typedef struct S_80017EB8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80017EB8_3;

typedef struct S_80017EB8_4 {
    s16 unk_00;
} S_80017EB8_4;

extern s32 func_800186D8();

typedef struct S_80017EB8_0 {
    u8 unk_00;
    u8 unk_01;
} S_80017EB8_0;   /* arg0 in check_selected_entry_8 */

/* Checks whether the selected entry is 8 or 9 and func_800186D8 returns zero. */
s32 check_selected_entry_8(S_80017EB8_0 *position) {
    s32 entry_value;
    u8 column;
    u8 row;

    row = position->unk_01;
    column = position->unk_00;
    entry_value = ((S_80017EB8_4 *)((column * 0x14) + ((S_80017EB8_3 *)(((row * 0x14)
        + ((s32)((TownResourceLinks *)D_80016000->unk_24)->gridRows))))->unk_0C))->unk_00;
    if (func_800186D8() == 0) {
        if ((u32)(entry_value - 8) < 2U) {
            return 1;
        }
    }
    return 0;
}
