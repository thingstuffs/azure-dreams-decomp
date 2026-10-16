/* Relink of matched town/func_800CC4F4; every changed retail word is a paired relocation. */
#define D_800C9864 D_800C9B44
#define D_800D64DC D_800D6518
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townInitializeObjectEntries();          /* extern */
extern M2C_UNK D_800C9B44;
extern M2C_UNK D_800D6518;


/* Initialize the object and set its handler. */
void func_800C9D40(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    townInitializeObjectEntries(object, context, &D_800D6518);
    object->unk_50.as_pm = &D_800C9B44;
}
