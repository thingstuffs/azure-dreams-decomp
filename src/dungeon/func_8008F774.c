#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

s16 dungeonFindFlaggedTileEntry();    /* extern */
u16 func_800BCB04();                   /* extern */


/* Call dungeonFindFlaggedTileEntry with a temporary tile-based value in unk_88. */
s16 dungeonCheckTileEntryAtAdjustedHeight(s32 context, M2C_UNK data, Rec_D_80082E80 *tile, EntityRec *state) {
    s16 result;
    u16 saved_value;

    saved_value = ((u16)state->unk_88);
    state->unk_88 = func_800BCB04((tile->unk_24 << 6) | 0x20, (tile->unk_25 << 6) | 0x20, (s16) (saved_value - 0x20));
    result = dungeonFindFlaggedTileEntry(context, data, tile, state);
    state->unk_88 = saved_value;
    return result;
}
