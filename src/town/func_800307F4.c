/* Relink of matched town/func_800CC4F4; every changed retail word is a paired relocation. */
#define D_800C9864 D_800CDADC
#define D_800D64DC D_800D72E8
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800C2E84();          /* extern */
extern M2C_UNK D_800CDADC;
extern M2C_UNK D_800D72E8;


/* Initialize the object and set its handler. */
void func_800CDF54(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    func_800C2E84(object, context, &D_800D72E8);
    object->unk_50.as_pm = &D_800CDADC;
}
