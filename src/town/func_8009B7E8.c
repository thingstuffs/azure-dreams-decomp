#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void func_80099754();                     /* extern */
extern M2C_UNK D_8009AA2C;
extern M2C_UNK D_800D00A8;


/* Clears the object's indexed flag and updates its state and handler. */
void func_80098F48(Rec_func_80094268_arg0 *object, s32 context, void *ptr2) {
    func_80094984((s32 *) &D_800D00A8, object, ptr2);
    D_80082660[object->unk_40].unk_00 = 0;
    object->unk_0A.as_s16 = 0xA;
    func_80099754(context);
    object->unk_04.as_pm = &D_8009AA2C;
}
