#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 func_80096788(EntityRec *);                                /* extern */
void func_800967E0();                 /* extern */
extern s32 D_800FE5D4;


/* Update the record to the computed upper bound when the global state permits. */
void func_80096810(EntityRec *record) {
    s32 upper_bound;

    if (D_800FE5D4 < 0) {
        upper_bound = (func_80096788(record) << 0x10) - 1;
        if (upper_bound >= record->z.v) {
            func_800967E0(record, upper_bound);
        }
    }
}
