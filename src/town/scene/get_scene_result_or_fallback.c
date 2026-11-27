#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/motion.h"

extern u8 D_80018B10[];
extern s32 library_lookup_context;
extern u8 D_8001B749[];
extern u8 D_8001BE29[];

/* Returns the entry's generated result or a fallback selected by condition 0x50F. */
void *get_scene_result_or_fallback(TownObjectSet *entry, s32 unused, s32 result_arg) {
    if (get_script_flag_mask(entry->entry_flag) == 0) {
        return apply_entry_position(D_80018B10, &library_lookup_context, entry, result_arg);
    }

    if (get_script_flag_mask(F_sbs07_pad24) != 0) {
        return D_8001BE29;
    }

    return D_8001B749;
}
