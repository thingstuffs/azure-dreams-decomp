#include "common.h"
#include "m2c_compat.h"

s16 find_min_qualifying_plane_height();          /* extern */

typedef struct S_8008CF48_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8008CF48_0;   /* arg0 in forward_surface_query_with_argument */

/* Pass three signed record components and a query argument to find_min_qualifying_plane_height. */
s16 forward_surface_query_with_argument(S_8008CF48_0 *record, M2C_UNK query_arg) {
    return find_min_qualifying_plane_height(record->unk_02, record->unk_06, record->unk_0A, query_arg);
}
