#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_800AA844;
extern s32 D_800D0138;


/* Initialize the record, set its first pointer to D_800AA844, and store code 0x54. */
void func_800AAA58(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    func_80094984((s32 *) &D_800D0138, record, ptr2);
    record->unk_00.as_pm = &D_800AA844;
    record->unk_0A.as_s16 = 0x15;
}
