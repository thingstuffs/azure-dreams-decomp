#include "common.h"
#include "m2c_compat.h"

void townClearReferencedObjectActiveFlag();                            /* extern */
s32 townGetScriptFlagMask();                             /* extern */
extern s16 D_8001B8AA;

/* Call townClearReferencedObjectActiveFlag when the current check returns zero, then return one. */
s32 townCallHandlerWhenCheckClear(void) {
    if (townGetScriptFlagMask(D_8001B8AA) == 0) {
        townClearReferencedObjectActiveFlag();
    }
    return 1;
}
