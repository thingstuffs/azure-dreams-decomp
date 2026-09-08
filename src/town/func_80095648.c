#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8009451C();        /* extern */
M2C_UNK func_80094714();        /* extern */
M2C_UNK func_80094910();                            /* extern */
M2C_UNK func_80094C1C();                         /* extern */
M2C_UNK func_80094C74();                      /* extern */
M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800954F4();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_800ABD74();                      /* extern */
extern u8 D_80083160[];
extern u8 D_800CFCEF;
extern M2C_UNK D_800FE488;

typedef struct S_80092DA8_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092DA8_0;   /* town_state in func_80092DA8 */


/* Updates a town object based on its threshold and the global update flag. */
void func_80092DA8(s32 object_id, Rec_D_800E3D7C *object, M2C_UNK update_context) {
    s16 update_threshold;
    u8 *town_state;

    town_state = D_80083160;
    func_80095C80(object);
    func_80094C1C(object_id);
    func_80094C74(object);
    if (((S_80092DA8_0 *)town_state)->unk_10 & 0x40) {
        func_80094714(object_id, object, update_context);
    }
    update_threshold = func_80095978(object, &D_800FE488);
    if (object->unk_08.at02_s16.v >= update_threshold) {
        func_80094910();
        func_80095A94(object, update_threshold, &D_800FE488);
        func_800ABD74(object);
        goto shared_update;
    }

    if (D_800CFCEF == 0) {
        goto no_update;
    }
    func_80094910();
    object->unk_14.as_s32 = 0;
    func_800954F4(object);

shared_update:
    func_8009451C(object_id, object, update_context);
    return;

no_update:
    func_80095388(object);
}
