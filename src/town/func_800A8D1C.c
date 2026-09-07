/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A63C8();                         /* extern */
extern s8 ***D_80081458;
extern s32 D_80100E2C[3];

void func_800A647C(s32 arg0) {
    s32 shifted = arg0 << 0x10;
    s32 addr;
    addr = (shifted >> 0xE) + (s32)**D_80081458;
    
    func_800A63C8(*(s32 *)addr);
    D_80100E2C[0] = 0;
}
