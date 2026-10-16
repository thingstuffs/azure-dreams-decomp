#include "common.h"
#include "m2c_compat.h"

void dungeonPassGlobalDataWithFixedArgs();                            /* extern */
s32 dungeonLinkIndexedEntryChain();                    /* extern */
void dungeonSetAttachedObjectPosition(s32 *, s32);                            /* extern */
void dungeonInitializeNineEntryLinks();              /* extern */

/* Run both setup calls, compute the result from the pointed value, and finalize. */
s32 dungeonRunObjectSetupAndFinalize(s32 *value_ptr, s32 context) {
    s32 result;

    dungeonSetAttachedObjectPosition(value_ptr, context);
    dungeonInitializeNineEntryLinks(value_ptr, context);
    result = dungeonLinkIndexedEntryChain(*value_ptr, context);
    dungeonPassGlobalDataWithFixedArgs();
    return result;
}
