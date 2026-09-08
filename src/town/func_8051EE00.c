#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017D80();             /* extern */
M2C_UNK func_80018A64();                         /* extern */
M2C_UNK func_80018ADC();                     /* extern */

typedef struct S_8051EE00_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8051EE00_0;   /* arg0 in func_8051EE00 */

/* Apply operation 0x5BC and the record code, then dispatch the record and context. */
void func_8051EE00(S_8051EE00_0 *record, M2C_UNK context) {
    func_80018ADC(0x5BC);
    func_80018A64(record->unk_18);
    func_80017D80(record, context);
}
