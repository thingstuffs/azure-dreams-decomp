#include "town/scene.h"
#include "town/player.h"
#include "town/scene/flags.h"


/* Raise the fixed script flag used by this scene's setup callers. */
void set_script_flag_94c(void)
{
    set_scene_script_flag_bit(0x94C);
}
