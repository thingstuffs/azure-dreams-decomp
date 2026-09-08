#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800E2804;
extern M2C_UNK D_800E2828;
extern M2C_UNK D_800E28B8;

typedef struct S_800DCCF4_0 {
    s32 unk_00;
    M2C_UNK * unk_04;
    M2C_UNK * unk_08;
    M2C_UNK * unk_0C;
} S_800DCCF4_0;   /* arg0 in func_800DCCF4 */


M2C_UNK func_800DCC3C(S_800DCCF4_0 *);
/* Assign the object tables and mode, then initialize the object. */
s32 func_800DCCF4(S_800DCCF4_0 *object, s32 mode) {
    object->unk_04 = &D_800E2828;
    object->unk_08 = &D_800E28B8;
    object->unk_00 = mode;
    object->unk_0C = &D_800E2804;
    func_800DCC3C(object);
    return 1;
}
