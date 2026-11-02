#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "shared/town_root.h"

/* Decrements the current entry's counter for 0x5C8, otherwise checks 0x11FC. */
s32 tick_scene_counter(void) {
    s32 result;

    if (get_script_flag_mask(F_sbs11_pad37) != 0) {
        {
            Rec_D_80016000 *context;
            u8 *entry;

            context = town_scene_root;
            entry = (u8 *)((context->entry_index << 3) + *(s32 *)((u8 *)context + 0x40));
            entry[1] -= 1;
        }
        result = 0;
        {
            void *context;
            u8 *entry;

            context = (void *)town_scene_root;
            entry = (u8 *)((*(s32 *)((u8 *)context + 8) << 3) + *(s32 *)((u8 *)context + 0x40));

            if (entry[1] == 0) {
                clear_script_flag_bit(F_sbs11_pad37);
            }
        }
        return result;
    }
    result = get_script_flag_mask(Fp_pool_open) != 0;
    return result;
}
