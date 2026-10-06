#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"

M2C_UNK func_8009451C();        /* extern */
M2C_UNK func_80094714();        /* extern */
M2C_UNK func_80094910();                            /* extern */
void func_80094C1C();                         /* extern */
void func_80094C74();                      /* extern */
void func_80095388();                      /* extern */
void func_800954F4();                      /* extern */
s16 func_80095978();               /* extern */
void func_80095A94();      /* extern */
void func_80095C80();                      /* extern */
void func_800ABD74();                      /* extern */
extern u8 D_800CFCEF;


/* Updates a town object based on its threshold and the global update flag. */
void func_80092DA8(s32 object_id, EntityRec *object, s32 update_context) {
    s16 update_threshold;
    GameWork *town_state;

    town_state = &gameWork;
    func_80095C80(object);
    func_80094C1C(object_id);
    func_80094C74(object);
    if (((s32)town_state->unk_010) & 0x40) {
        func_80094714(object_id, object, update_context);
    }
    update_threshold = func_80095978(object, &D_800FE488);
    if (object->z.w.i >= update_threshold) {
        func_80094910();
        func_80095A94(object, update_threshold, &D_800FE488);
        func_800ABD74(object);
        func_8009451C(object_id, object, update_context);
    } else if (D_800CFCEF != 0) {
        func_80094910();
        object->flags14 = 0;
        func_800954F4(object);
        func_8009451C(object_id, object, update_context);
    } else {
        func_80095388(object);
    }
}
