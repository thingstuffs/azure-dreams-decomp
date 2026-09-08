#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

typedef struct S_8009DD40_0_pre {
    u16 unk_00;
} S_8009DD40_0_pre;   /* the 0x2 bytes before arg0 in func_8009DD40, addressed as arg0[-1] */



M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_800478B8();                     /* extern */
M2C_UNK func_8008F134();                      /* extern */
s32 func_80096FF4();                         /* extern */
M2C_UNK func_800970AC();                 /* extern */
s32 func_8009D20C(void *, M2C_UNK);                                /* extern */
extern s32 D_800814A0[];

/* Cleans up an object when its state check succeeds, or dispatches its callback and updates it. */
void func_8009DD40(void *object, M2C_UNK source, M2C_UNK context) {
    s8 *status_ptr;

    if (func_8009D20C(object, source) != 0) {
        func_8008F134(object);
        status_ptr = ((Rec_D_80082D58 *)object)->unk_98.as_ps8;
        if (status_ptr != NULL) {
            *status_ptr = 0;
        }
        func_80033D08(object);
        ((S_8009DD40_0_pre *)object)[-1].unk_00 = (u16) (((S_8009DD40_0_pre *)object)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        return;
    }
    ((Rec_D_80082D58 *)object)->unk_50.as_x151a23(object, object, source, context);
    if (!(((S_8009DD40_0_pre *)object)[-1].unk_00 & 0x8000)) {
        func_800970AC(func_80096FF4(source), object);
        if (((Rec_D_80082D58 *)object)->unk_4D == 0x13) {
            func_800478B8(context);
        }
    }
}
