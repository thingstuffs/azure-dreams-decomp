#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void func_80095388();                 /* extern */
s16 func_80095978();               /* extern */
void func_80095A94();      /* extern */
void func_80098928();        /* extern */
extern M2C_UNK D_800FE488;


/* Advance the object's position and handle crossing the sampled limit. */
void func_80099B70(s32 context, EntityRec *object, s32 update_data) {
    s16 limit;

    object->z.v = (s32) (object->z.v + object->flags14);
    limit = func_80095978(object, &D_800FE488);
    if (limit < object->z.w.i) {
        func_80095A94(object, limit, &D_800FE488);
        func_80098928(context, object, update_data);
        return;
    }
    func_80095388(object);
}
