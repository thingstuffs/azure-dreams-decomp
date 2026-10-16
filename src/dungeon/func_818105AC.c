#include "common.h"
#include "m2c_compat.h"

void inventorySetEmbeddedStateFour();                         /* extern */

typedef struct S_800255AC_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_800255AC_0;   /* arg0 in dungeonForwardStoredObjectValue */

/* Passes the object's stored value to inventorySetEmbeddedStateFour. */
void dungeonForwardStoredObjectValue(S_800255AC_0 *object) {
    inventorySetEmbeddedStateFour(object->unk_40);
}
