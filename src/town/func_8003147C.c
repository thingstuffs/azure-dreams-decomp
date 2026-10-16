/* Relink of matched town/func_800CA950; every changed retail word is a paired relocation. */
#define D_80082680 D_80082688
#define D_800C7EF0 D_800CE538
#define D_800D5FA0 D_800D72C0
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800C2E84();          /* extern */
extern s8 D_80082688;
extern M2C_UNK D_800CE538;
extern M2C_UNK D_800D72C0;


/* Initialize the object callback and clear its state values. */
void func_800CEBDC(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK init_data) {
    func_800C2E84(object, init_data, &D_800D72C0);
    D_80082688 = 0;
    object->unk_54 = &D_800CE538;
    object->unk_72.as_s16 = 0;
}
