#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_effect_views.h"

struct Rec_func_800B0C68_arg0; void position_shop_row_widgets(struct Rec_func_800B0C68_arg0 *);                      /* extern */


/* Store a value in the embedded record and process the record. */
void store_shop_embedded_value(s32 base_addr, s32 value) {
    EffectStateWordView *record;

    record = base_addr + 0x20;
    record->unk_08 = value;
    position_shop_row_widgets((struct Rec_func_800B0C68_arg0 *)(record));
}
