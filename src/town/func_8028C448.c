/* Relink of matched town/func_8032C0AC; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"

void townApplySelectedEntryValues(s32, s32);             /* extern */
void townSetCurrentEntryScriptFlag(void);                 /* extern */
s32 townGetLinkedRecordField2D60(void);                  /* extern */

/* Process the request after checking the threshold of 15. */
void func_80016C48(s32 request, M2C_UNK context) {
    if (townGetLinkedRecordField2D60() >= 0xF) {
        townSetCurrentEntryScriptFlag();
    }
    townApplySelectedEntryValues(request, context);
}
