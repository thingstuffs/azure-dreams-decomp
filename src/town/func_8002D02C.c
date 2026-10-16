/* Relink of matched town/func_800CA950; every changed retail word is a paired relocation. */
#define D_80082680 D_800826B8
#define D_800C7EF0 D_800CA3EC
#define D_800D5FA0 D_800D64C8
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townInitializeObjectEntries();          /* extern */
extern s8 D_800826B8;
extern M2C_UNK D_800CA3EC;
extern M2C_UNK D_800D64C8;


/* Initialize the object callback and clear its state values. */
void func_800CA78C(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK init_data) {
    townInitializeObjectEntries(object, init_data, &D_800D64C8);
    D_800826B8 = 0;
    object->unk_54 = &D_800CA3EC;
    object->unk_72.as_s16 = 0;
}
