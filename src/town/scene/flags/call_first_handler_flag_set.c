#include "script_symbols.h"
#include "common.h"

extern s32 func_800175BC(s32);
extern void func_80016A78(void);
extern void func_80016B20(s32, s32);

/* If flag 0x3EC is set, call func_80016A78 first; then func_80016B20(target, value). */
void call_first_handler_if_flag_0x3ec_set(s32 target, s32 value) {
    if (func_800175BC(Ft_game_clr) != 0) {
        func_80016A78();
    }
    func_80016B20(target, value);
}
