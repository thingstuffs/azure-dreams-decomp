#include "common.h"
#include "m2c_compat.h"
#include "shared/types3a_types.h"

s16 find_highest_surface_within_range();                   /* extern */

   /* arg0 in forward_highest_surface_query */

/* Pass three signed record components to find_highest_surface_within_range. */
s16 forward_highest_surface_query(SignedPositionView *record) {
    return find_highest_surface_within_range(record->unk_02, record->unk_06, record->unk_0A);
}
