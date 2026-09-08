/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A63C8();                         /* extern */
extern s8 ***D_80081458;
extern s32 D_80100E2C[3];

/* Apply the table entry selected by the signed low-halfword index and clear pending state. */
void func_800A647C(s32 index) {
    s32 shifted_index = index << 0x10;
    s32 entry_address;
    entry_address = (shifted_index >> 0xE) + (s32)**D_80081458;
    
    func_800A63C8(*(s32 *)entry_address);
    D_80100E2C[0] = 0;
}
