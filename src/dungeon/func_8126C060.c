/* Relink of matched dungeon/func_81254060; every changed retail word is a paired relocation. */
#define D_80173FC8 D_8015BFC8
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

M2C_UNK func_800353F4();                   /* extern */
extern M2C_UNK D_8015BFC8;

typedef struct S_81254060_0 {
    u8 pad_00[0x6D];
    s8 unk_6D;
} S_81254060_0;   /* arg3 in func_8015B860 */

typedef struct S_81254060_1 {
    u8 pad_00[0x9B];
    s8 unk_9B;
} S_81254060_1;   /* arg0 in func_8015B860 */

/* Runs the global handler and clears both record flags when bit 21 is set. */
void func_8015B860(S_81254060_1 *primary_record, M2C_UNK unused_1, M2C_UNK unused_2, S_81254060_0 *secondary_record) {
    if (((s32)g_game_work.unk_010) & 0x200000) {
        func_800353F4(&D_8015BFC8);
        secondary_record->unk_6D = 0;
        primary_record->unk_9B = 0;
    }
}
