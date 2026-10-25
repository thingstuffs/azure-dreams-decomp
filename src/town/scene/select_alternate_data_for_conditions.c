#include "script_symbols.h"
#include "town/scene.h"
#include "common.h"

extern s32 func_800198D0(s32);
extern s32 D_8001638C;

/* Select alternate output data when condition 0x3F5 is clear and condition 0x14 is set. */
s32 *select_alternate_data_for_conditions(s32 **out_data) {
    if (func_800198D0(F_sbs01_pad00) == 0) {
        if (func_800198D0(sn_open_sekkyo_end) != 0) {
            *out_data = get_data_pointer_1691_c;
            return 0;
        }
    }
    return &D_8001638C;
}
