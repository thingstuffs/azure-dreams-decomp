#include "script_symbols.h"
#include "common.h"
#include "town/scene/flags.h"
#include "town/player/state.h"
#include "town/scene.h"

extern void func_800178D0(void);

/* If flag 0x3EC is set, call func_800178D0 first; then func_80017978(target, value). */
void process_entry_after_game_clear_b(s32 target, s32 value) {
    if (get_script_flag_mask(Ft_game_clr) != 0) {
        func_800178D0();
    }
    process_checked_entry(target, value);
}
