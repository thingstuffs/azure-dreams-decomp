#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_80099E70_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80099E70_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in func_80099E70 */




M2C_UNK func_80094984();                 /* extern */
extern u8 D_80082660;
extern M2C_UNK D_80099874;


/* Processes the linked object, then clears the slot flag and resets the record state. */
void func_80099E70(Rec_func_80094268_arg0 *record) {
    func_80094984(((S_80099E70_2 *)(((Rec_func_80094268_arg0 *)record)->unk_44))->unk_14, record);
    *((record->unk_40 * 8) + &D_80082660) = 0;
    record->unk_04.as_pm = &D_80099874;
    record->unk_10.as_s16 = 0;
}
