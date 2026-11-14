#include "common.h"
#include "m2c_compat.h"

#include "engine/object.h"

typedef struct S_80033D38_0 {
    s32 unk_00;
} S_80033D38_0;   /* arg0 in is_node_registered; pointer addresses record offset 0xC */


/* Checks whether the record field 12 bytes before record_data is nonzero. */
s32 is_node_registered(void *record_data) {
    return ((S_80033D38_0 *)((u8 *)record_data - 0xC))->unk_00 != 0;
}
