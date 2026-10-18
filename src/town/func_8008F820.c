#include "common.h"
#include "m2c_compat.h"

s16 find_highest_surface_within_range();                   /* extern */

typedef struct S_8008CF80_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8008CF80_0;   /* arg0 in forward_highest_surface_query */

/* Pass three signed record components to find_highest_surface_within_range. */
s16 forward_highest_surface_query(S_8008CF80_0 *record) {
    return find_highest_surface_within_range(record->unk_02, record->unk_06, record->unk_0A);
}
