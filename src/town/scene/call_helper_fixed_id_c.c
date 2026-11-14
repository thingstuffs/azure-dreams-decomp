#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Calls func_80018C74 with Ft_cheriru_love. */
void set_cheriru_love_flag(void) { set_script_flag_bit(Ft_cheriru_love); }
