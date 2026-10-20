#include "script_symbols.h"
#include "common.h"

extern s32 func_80018640(s32);
extern void func_800178D0(void);
extern void func_80017978(s32, s32);

/* If flag 0x3EC is set, call func_800178D0 first; then func_80017978(target, value). */
void run_handler_after_flag_3ec(s32 target, s32 value) {
    if (func_80018640(Ft_game_clr) != 0) {
        func_800178D0();
    }
    func_80017978(target, value);
}
