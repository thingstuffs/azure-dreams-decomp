#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void func_80095388();                      /* extern */
s16 func_800C2B38();                          /* extern */
void func_800C4174();

/* extern */

/* Advance the object's fixed-point value and clamp it when it exceeds the limit. */
void func_800C3EAC(s32 context, EntityRec *object, s32 update_data) {
    object->z.v = (s32) (object->z.v + object->flags14);
    if (func_800C2B38(object) < object->z.w.i) {
        object->z.w.i = func_800C2B38(object);
        func_800C4174(context, object, update_data);
        return;
    }
    func_80095388(object);
}
