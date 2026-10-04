#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_800954C4(EntityRec *);                            /* extern */
extern s8 D_800CFCEA;


/* Set D_800CFCEA, initialize the record, and call func_800954C4. */
void func_800966F8(EntityRec *record, s32 initial_value) {
    D_800CFCEA = 1;
    record->x.v = initial_value;
    record->unk_0C = 0;
    func_800954C4(record);
}
