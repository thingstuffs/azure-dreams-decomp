/* Relinked copy of town/func_808B82AC (func_808B82AC.c); retail differs only at relocation sites. */
#include "common.h"

extern s32 D_00003F54[];
extern s32 D_00004134[];
extern s8 D_00004140[];
extern s32 D_000045F8[];

/* Return the base value plus the signed-index table adjustment. */
s32 get_adjusted_base_value(void) {
    return D_000045F8[0] + D_00004134[D_00004140[D_00003F54[0]]];
}
