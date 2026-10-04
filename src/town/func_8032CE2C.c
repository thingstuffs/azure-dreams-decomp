#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 func_80019B54();             /* extern */
void func_8001ACE8();                         /* extern */
s32 func_8001ADE0();                         /* extern */


/* Applies the object's stored value when either condition is active, then forwards the call. */
void func_8001762C(Rec_func_800165F4_arg0 *object, s32 context) {
    if ((func_8001ADE0(0x1388) != 0) || (func_8001ADE0(0x138A) != 0)) {
        func_8001ACE8(object->unk_18);
    }
    func_80019B54(object, context);
}
