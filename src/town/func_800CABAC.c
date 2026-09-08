#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C830C_0 {
    u8 pad_00[0x74];
    s32 unk_74;
} S_800C830C_0;   /* D_80082674 in func_800C830C */


extern S_800C830C_0 *D_80082674;
extern s32 D_800D61F8[];

/* mascot_anime_chg: sets the reserved dungeon from the indexed script value. */
void func_800C830C(s32 value_index) {
    D_80082674->unk_74 = D_800D61F8[value_index];
}
