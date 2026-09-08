#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800954F4(Rec_D_800E3D7C *);                            /* extern */
extern s8 D_800CFCE8;


/* Set the record value, clear its secondary value, and refresh it with the global flag set. */
void func_800967E0(Rec_D_800E3D7C *record, s32 value) {
    D_800CFCE8 = 1;
    record->unk_08.at00_s32.v = value;
    record->unk_14.as_s32 = 0;
    func_800954F4(record);
}
