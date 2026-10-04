#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BDFA0_0 {
    u8 pad_00[0x68];
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x36];
    s32 unk_A0;
    s32 unk_A4;
} S_800BDFA0_0;   /* record in func_800BDFA0 */


s32 func_800352FC(void);                                /* extern */
M2C_UNK func_8003DB94();       /* extern */
M2C_UNK func_800478B8();                     /* extern */
s32 func_800C2AB4();                          /* extern */

void func_800BDFA0(S_800BDFA0_0 *record, M2C_UNK unused, M2C_UNK value) {
    s16 state;

    func_800478B8(value);
    state = record->unk_68.s;
    switch (state) {
    case 0:
        if ((func_800352FC() != 0) && (func_800C2AB4(record) != 0)) {
            func_8003DB94(value, record->unk_A4, 0);
            record->unk_68.u++;
        }
        break;
    case 1:
        if ((func_800352FC() == 0) || (func_800C2AB4(record) == 0)) {
            record->unk_68.u++;
        }
        break;
    case 2:
        if ((func_800352FC() != 0) && (func_800C2AB4(record) != 0)) {
            func_8003DB94(value, record->unk_A0, 0);
            record->unk_68.u++;
        }
        break;
    case 3:
        if ((func_800352FC() == 0) || (func_800C2AB4(record) == 0)) {
            record->unk_68.s = 0;
        }
        break;
    }
}
