#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800954F4(EntityRec *);                            /* extern */
extern s8 D_800CFCE8;


/* Set the record value, clear its secondary value, and refresh it with the global flag set. */
void func_800967E0(EntityRec *record, s32 value) {
    D_800CFCE8 = 1;
    record->z.v = value;
    record->flags14 = 0;
    func_800954F4(record);
}
