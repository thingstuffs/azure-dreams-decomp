#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016104();     /* extern */
M2C_UNK func_80018ADC();                     /* extern */
extern M2C_UNK D_80018E48;

/* Apply operation 0x5BE and dispatch D_80018E48 with the supplied value and context. */
void func_80016A20(s32 value, M2C_UNK unused, M2C_UNK context) {
    func_80018ADC(0x5BE);
    func_80016104(&D_80018E48, value, context);
}
