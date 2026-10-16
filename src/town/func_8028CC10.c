/* Relink of matched town/func_8032C958; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017158_0 {
    s32 unk_00;
} S_80017158_0;   /* arg0 in func_80017410; pointer addresses record offset 0x1C */


s32 townProcessCheckedEntry(void *, s32);                                /* extern */

/* Set the record flag 0x8000 when the query returns zero and return the query result. */
s32 func_80017410(void *record_field, s32 query_value) {
    s32 query_result;

    query_result = townProcessCheckedEntry(record_field, query_value);
    if (query_result == 0) {
        ((S_80017158_0 *)((u8 *)record_field - 0x1C))->unk_00 = (s32) (((S_80017158_0 *)((u8 *)record_field
            - 0x1C))->unk_00 | 0x8000);
    }
    return query_result;
}
