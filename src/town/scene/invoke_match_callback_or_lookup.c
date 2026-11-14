#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"

void invoke_match_callback_or_lookup(void)
{
    s32 lookup_result;

    if (check_callback_record_bytes(0xD, 3) != 0) {
        (*((s32 (**)(s32))
            (((s8 *) (*((void **) (((s8 *) town_scene_root) + 0x20)))) + 0x78)))(0);
        return;
    }
    lookup_result = find_entry_index_by_grid_bytes(0xD, 3);
    if (lookup_result != (-1)) {
        release_lshop_entry_and_compact(lookup_result);
    }
}
