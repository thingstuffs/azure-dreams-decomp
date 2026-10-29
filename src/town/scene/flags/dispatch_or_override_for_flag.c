#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

extern s32 D_8001BB6C;
extern s32 scene_dispatch_context;
extern u8 D_8001F8B5[];


/* Return the dispatch result, overriding it when the 0x1390 check succeeds. */
u8 *dispatch_or_override_for_flag_1390(s32 dispatch_arg, s32 unused, s32 dispatch_option) {
    u8 *result;
    s32 first_arg = dispatch_arg;
    s32 fourth_arg = dispatch_option;


    result = apply_entry_position(&D_8001BB6C, &scene_dispatch_context, first_arg, fourth_arg);
    if (get_script_flag_mask(F_selfy_dungeon_kenka_b) != 0) {
        return D_8001F8B5;
    }
    return result;
}
