#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"


typedef struct S_8009A1A4_2 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_8009A1A4_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in func_8009A1A4 */


extern M2C_UNK D_80099B70;


/* Set up the object using its linked record and assign its next handler. */
void func_8009A1A4(Rec_func_80094268_arg0 *object, void *ptr, void *ptr2) {
    func_80094984((s32 *) ((S_8009A1A4_2 *)(((Rec_func_80094268_arg0 *)object)->unk_44))->unk_20, object, ptr2);
    object->unk_04.as_pm = &D_80099B70;
}
