#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"
#include "town/scene.h"

extern void func_80016A78(void);

/* If flag 0x3EC is set, call func_80016A78 first; then func_80016B20(target, value). */
void process_entry_after_game_clear_a(s32 target, s32 value) {
    if (get_script_flag_mask(Ft_game_clr) != 0) {
        func_80016A78();
    }
    process_checked_entry(target, value);
}
