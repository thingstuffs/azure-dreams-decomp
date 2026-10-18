#include "common.h"

s32 *func_80017D80();             /* extern */
s32 func_80018A64(s32);
s32 func_80018ADC(s32);

typedef struct S_8051EE00_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8051EE00_0;   /* arg0 in func_8051EE00 */

/* Apply operation 0x5BC and the record code, then dispatch the record and context. */
void func_8051EE00(S_8051EE00_0 *record, s32 context) {
    func_80018ADC(0x5BC);
    func_80018A64(record->unk_18);
    func_80017D80(record, context);
}
