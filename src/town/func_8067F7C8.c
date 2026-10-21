/* Relinked copy of town/func_8032E22C (func_8032E22C.c); retail differs only at relocation sites. */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



extern u32 scene_money_adjustment;


/* Checks whether the stored value meets the D_800188C8 threshold. */
s32 func_800167C8(void) {
    return (u32) D_80016000->unk_38->unk_2D5C >= (u32) scene_money_adjustment;
}
