#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"

void func_8008F664();           /* extern */
void func_8009065C();     /* extern */
void func_8009539C();                      /* extern */
void func_800953D0();                      /* extern */
void func_80095460();                      /* extern */
void func_80095910();                   /* extern */
s32 func_80096FF4();                      /* extern */
void func_800A573C();     /* extern */
extern s32 D_800903FC[];
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800FE490;


typedef struct S_800A5638_0_pre {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
} S_800A5638_0_pre;   /* the 0x10 bytes before arg0 in func_800A5638, addressed as arg0[-1] */


/* Updates the record, invokes its handler, clamps values, and dispatches follow-up processing. */
void func_800A5638(void *handler, EntityRec *record, s32 context) {
    func_800953D0(record);
    func_80095910(&D_800FE490);
    func_8009539C(record);
    func_80096FF4(record);
    func_80095460(record);
    func_8008F664(&D_800CFCB4, record);
    ((Rec_func_8009431C_arg0 *)handler)->unk_00.as_x78b360(handler, record, context);
    if (!(((S_800A5638_0_pre *)handler)[-1].unk_0E & 0x8000)) {
        if (record->y.v <= 0x06500000) {
            record->y.v = 0x06500000;
            record->unk_10 = 0x180000;
            if (record->z.v > 0) {
                record->z.v = 0;
            }
        }
        if (((S_800A5638_0_pre *)handler)[-1].unk_00 == &D_800903FC) {
            func_8009065C(handler, record, context);
            return;
        }
        func_800A573C(handler, record, context);
    }
}
