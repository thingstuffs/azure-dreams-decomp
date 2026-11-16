#include "script_symbols.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/scene/flags.h"
#include "town/player/state.h"


/* Set script flag F_sbs32_pad34 for this scene's setup callers. */
void set_script_flag_sbs32_pad34(void)
{
    set_script_flag_bit(F_sbs32_pad34);
}
