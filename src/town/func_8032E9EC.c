#include "common.h"
#include "m2c_compat.h"

void townSetScriptFlagBit();                     /* extern */

typedef struct S_800191EC_0 {
    u8 unk_00;
    u8 unk_01;
} S_800191EC_0;   /* arg0 in townSetLshopSpecialFlag */

/* Set flag 0x11F8 when the record bytes are 2 and 0xD. */
void townSetLshopSpecialFlag(S_800191EC_0 *record) {
    if ((record->unk_01 == 0xD) && (record->unk_00 == 2)) {
        townSetScriptFlagBit(0x11F8);
    }
}
