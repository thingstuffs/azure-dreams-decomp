#include "common.h"
#include "shared/types3a_types.h"

s16 find_min_qualifying_plane_height();          /* extern */

   /* arg0 in forward_surface_query_with_argument */

/* Pass three signed record components and a query argument to find_min_qualifying_plane_height. */
s16 forward_surface_query_with_argument(SignedPositionView *record, s32 query_arg) {
    return find_min_qualifying_plane_height(record->unk_02, record->unk_06, record->unk_0A, query_arg);
}
