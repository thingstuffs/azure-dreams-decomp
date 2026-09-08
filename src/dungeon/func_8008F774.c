#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

s16 func_80095464();    /* extern */
u16 func_800BCB04();                   /* extern */



/* Call func_80095464 with a temporary tile-based value in unk_88. */
s16 func_80094ED4(s32 context, M2C_UNK data, Rec_D_80082E80 *tile, Rec_D_800E3D7C *state) {
    s16 result;
    u16 saved_value;

    saved_value = state->unk_88.as_u16;
    state->unk_88.as_u16 = func_800BCB04((tile->unk_24 << 6) | 0x20, (tile->unk_25 << 6) | 0x20, (s16) (saved_value - 0x20));
    result = func_80095464(context, data, tile, state);
    state->unk_88.as_u16 = saved_value;
    return result;
}
