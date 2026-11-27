#include "common.h"
#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

s32 skip_hospital_scene02_after_cherrl_scene03(SquareSceneEntry *entry, s32 index)
{
    if (get_script_flag_mask(Fr_cheriru_scene03) != 0) {
        set_script_flag_bit(Fr_hospital_scene02);
        return 1;
    }

    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);
    return 0;
}
