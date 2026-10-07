/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern s32 D_00003F50;
extern s32 D_00003F54;

M2C_UNK func_80003544();                     /* extern */
M2C_UNK func_800035D4();                     /* extern */
s32 func_800037B8();                                /* extern */
M2C_UNK func_80003814();                            /* extern */
s32 func_8000386C();                             /* extern */
M2C_UNK func_800038B8();                            /* extern */
M2C_UNK func_80003DF0();                    /* extern */

/* Captures a value and its associated result, applies both, and returns the stored value. */
s32 func_808B8108(void) {
    s32 captured_value;

    func_800035D4(0);
    func_80003814();
    captured_value = func_800037B8();
    D_00003F50 = captured_value;
    D_00003F54 = func_8000386C(captured_value);
    func_800038B8();
    func_80003544(0);
    func_80003DF0(D_00003F50, D_00003F54);
    return D_00003F50;
}
