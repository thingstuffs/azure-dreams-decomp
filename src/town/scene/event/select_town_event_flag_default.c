#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 (*TownCallback)();

extern void func_80018B58(s32 bit_index);
extern void func_80018BD0(s32 bit_index);
extern s32 func_80018C50(s32 flagIndex);
extern s8 D_8001BD48[];

/* Selects a town event from flag checks or invokes the default town callback. */
s32 select_town_event_flag_default(void) {
    void *town;

    func_80018BD0(F_hos_first_cheriru);
    func_80018BD0(F_hos_first_hush);

    if (func_80018C50(F_first_nurse_event) == 0) {
        town = *(void **)((s8 *)(&town_scene_root));
        *(void **)((s8 *)*(void **)((s8 *)town + 0x1C) + 0x40) = D_8001BD48;
        (*(TownCallback *)((s8 *)*(void **)((s8 *)town + 0x20) + 0x2F8))(0x10, 0x200);
        return 0;
    }

    if ((func_80018C50(F_sbs16_top) != 0) &&
        (func_80018C50(F_sbs16_pad00) == 0) &&
        (func_80018C50(Ft_cheril_minikita) != 0)) {
        func_80018B58(F_sbs16_pad05);
        return 1;
    }

    (*(TownCallback *)((s8 *)*(void **)((s8 *)*(void **)((s8 *)(&town_scene_root)) + 0x20) + 0x2F8))(0x10, 0x200);
    return 0;
}
