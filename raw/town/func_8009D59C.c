/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void func_80099754();                     
extern s32 D_8009AD70;
extern s32 D_800D0198;

void func_8009ACFC(Rec_func_80094268_arg0 *object, s32 context, void *ptr2) {
    func_80094984((s32 *) &D_800D0198, object, ptr2);
    D_80082660[object->unk_40].unk_00 = 0;
    object->unk_0A.as_s16 = 0x14;
    func_80099754(context);
    object->unk_04.as_pm = &D_8009AD70;
}
