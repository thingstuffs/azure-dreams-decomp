#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

void set_script_flag_bit();                     /* extern */

typedef struct S_800191EC_0 {
    u8 unk_00;
    u8 unk_01;
} S_800191EC_0;   /* arg0 in set_lshop_special_flag */

/* Set flag 0x11F8 when the record bytes are 2 and 0xD. */
void set_lshop_special_flag(S_800191EC_0 *record) {
    if ((record->unk_01 == 0xD) && (record->unk_00 == 2)) {
        set_script_flag_bit(F_sell_mizu_medaru);
    }
}
