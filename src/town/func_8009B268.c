#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_80094984();  /* extern */
void func_80099754();                     /* extern */
extern M2C_UNK D_80097DE8;
extern M2C_UNK D_800D0178;


/* Initializes the object, assigns its handler table, and clears two global flags. */
void func_800989C8(Rec_func_80094268_arg0 *object, s32 setupValue, s32 initializationValue) {
    func_80099754(setupValue);
    func_80094984(&D_800D0178, object, initializationValue);
    object->unk_04.as_pm = &D_80097DE8;
    D_80082660[1].unk_00 = 0;
    D_80082660[1].unk_01 = 0;
}
