#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


/* Clears the record's three fields at offsets 0x0C through 0x14. */
void func_80099754(EntityRec *record) {
    record->unk_0C = 0;
    record->unk_10 = 0;
    record->flags14 = 0;
}
