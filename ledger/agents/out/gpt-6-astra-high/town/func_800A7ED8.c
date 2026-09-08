#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8008F664();           /* extern */
M2C_UNK func_8009065C();     /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800953D0();                      /* extern */
M2C_UNK func_80095460();                      /* extern */
M2C_UNK func_80095910();                   /* extern */
M2C_UNK func_80096FF4();                      /* extern */
M2C_UNK func_800A573C();     /* extern */
extern M2C_UNK D_800903FC;
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800FE490;


typedef struct S_800A5638_0_pre {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
} S_800A5638_0_pre;   /* the 0x10 bytes before arg0 in func_800A5638, addressed as arg0[-1] */

typedef struct S_800A5638_0 {
    M2C_UNK (*unk_00)(void *, void *, M2C_UNK);
} S_800A5638_0;   /* arg0 in func_800A5638 */


/* Updates the record, invokes its handler, clamps values, and dispatches follow-up processing. */
void func_800A5638(void *handler, Rec_D_800E3D7C *record, M2C_UNK context) {
    func_800953D0(record);
    func_80095910(&D_800FE490);
    func_8009539C(record);
    func_80096FF4(record);
    func_80095460(record);
    func_8008F664(&D_800CFCB4, record);
    ((S_800A5638_0 *)handler)->unk_00(handler, record, context);
    if (!(((S_800A5638_0_pre *)handler)[-1].unk_0E & 0x8000)) {
        if (record->unk_04.at00_s32.v <= 0x06500000) {
            record->unk_04.at00_s32.v = 0x06500000;
            record->unk_10.at00_s32.v = 0x180000;
            if (record->unk_08.at00_s32.v > 0) {
                record->unk_08.at00_s32.v = 0;
            }
        }
        if (((S_800A5638_0_pre *)handler)[-1].unk_00 == &D_800903FC) {
            func_8009065C(handler, record, context);
            return;
        }
        func_800A573C(handler, record, context);
    }
}
