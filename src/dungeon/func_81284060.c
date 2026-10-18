/* Relink of matched dungeon/process_global_effect_flags at file 0x1274060; imports and data use paired retail relocations. */
#define g_game_work D_80084818
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

M2C_UNK func_8003500C();                   /* extern */
extern M2C_UNK D_8016CFC8;

typedef struct S_81254060_0 {
    u8 pad_00[0x6D];
    s8 unk_6D;
} S_81254060_0;   /* arg3 in func_8016C860 */

typedef struct S_81254060_1 {
    u8 pad_00[0x9B];
    s8 unk_9B;
} S_81254060_1;   /* arg0 in func_8016C860 */

/* Runs the global handler and clears both record flags when bit 21 is set. */
void func_8016C860(S_81254060_1 *primary_record, M2C_UNK unused_1, M2C_UNK unused_2, S_81254060_0 *secondary_record) {
    if (((s32)g_game_work.unk_010) & 0x200000) {
        func_8003500C(&D_8016CFC8);
        secondary_record->unk_6D = 0;
        primary_record->unk_9B = 0;
    }
}
