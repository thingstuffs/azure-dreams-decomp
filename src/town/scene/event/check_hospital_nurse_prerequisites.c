#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/event.h"
#include "shared/town_root.h"
#include "town/player/state.h"

typedef s32 (*TownCallback)();

extern s8 D_8001BD48[];

/* Selects a town event from flag checks or invokes the default town callback. */
s32 check_hospital_nurse_prerequisites(void) {
    void *town;

    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);

    if (get_script_flag_mask(F_first_nurse_event) == 0) {
        town = town_scene_root;
        *(void **)((s8 *)*(void **)((s8 *)town + 0x1C) + 0x40) = D_8001BD48;
        (*(TownCallback *)((s8 *)*(void **)((s8 *)town + 0x20) + 0x2F8))(0x10, 0x200);
        return 0;
    }

    if ((get_script_flag_mask(F_sbs16_top) != 0) &&
        (get_script_flag_mask(F_sbs16_pad00) == 0) &&
        (get_script_flag_mask(Ft_cheril_minikita) != 0)) {
        set_script_flag_bit(F_sbs16_pad05);
        return 1;
    }

    ((TownCallback)(town_scene_root->services->callback_2F8))(0x10, 0x200);
    return 0;
}
