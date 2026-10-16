/* Relink of matched town/func_800C55D4; every changed retail word is a paired relocation. */
#define townGetFacingSector func_800C2D94
/* cfail-repair: true-space rowbase definition */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082E80.h"

void townClearObjectStatusAndDispatchTarget();
extern u32 func_800C2D94(s32);


/* Store the value table, apply the selected value to the target, and clear its status byte. */
void func_800C2DBC(Rec_func_80094268_arg0 *object, Rec_D_80082E80 *target, s32 *value_table) {
    object->unk_78 = value_table;
    townClearObjectStatusAndDispatchTarget(object, target, object->unk_78[func_800C2D94(object->unk_72.as_s16)], 0);
    target->unk_05.as_s8 = 0;
}
