#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
void func_800C4174();        /* extern */

/* extern */

/* Advance the object's position and stop its movement when it exceeds the limit. */
void func_800C86EC(s32 context, EntityRec *object, s32 finish_arg) {
    object->z.v = (s32) (object->z.v + object->flags14);
    if (func_800C2AE8(object) < object->z.w.i) {
        object->z.w.i = func_800C2AE8(object);
        object->flags14 = 0;
        func_800C4174(context, object, finish_arg);
        return;
    }
    func_80095388(object);
}
