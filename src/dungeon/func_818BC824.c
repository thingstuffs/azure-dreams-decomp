#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8009D218(s32, s32);                 /* extern */
M2C_UNK func_800AD4D0();                      /* extern */
M2C_UNK func_800AD568();                      /* extern */
M2C_UNK func_800B4C7C(); /* extern */


/* Adds 0x200 to the object's unk_64 and runs callbacks when its mode-2 check returns zero. */
void func_818BC824(Rec_D_800E3D7C *object) {
    if (func_8009D218((s32)object, 2) == 0) {
        object->unk_64.as_u16 = (u16) (object->unk_64.as_u16 + 0x200);
        func_800AD568(object);
        func_800B4C7C(0x8004, object, (s16) object->unk_64.as_u16, 1);
        func_800AD4D0(object);
    }
}
