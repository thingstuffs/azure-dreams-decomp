#include "common.h"
#include "m2c_compat.h"

void townSetScriptFlagBit();                     /* extern */
s32 townGetScriptFlagMask();                         /* extern */

/* Process ID 0xD51 and return its preceding query result. */
s32 townQueryAndProcessEventD51(void) {
    s32 query_result;

    query_result = townGetScriptFlagMask(0xD51);
    townSetScriptFlagBit(0xD51);
    return query_result;
}
