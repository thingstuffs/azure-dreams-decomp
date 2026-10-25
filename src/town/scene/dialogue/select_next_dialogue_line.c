#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef s32 (*StateQuery)(s32);


extern s8 D_8001602A[];
extern s8 D_80016359[];
extern s8 D_800164CC[];
extern s8 D_8001688A[];
extern s8 D_80016BCF[];
extern s8 D_80016C24[];
extern s8 D_80016C77[];
extern s8 D_80016CCE[];
extern s8 D_80016D77[];
extern s8 D_80016E0C[];
extern s8 D_80017152[];
extern s8 D_800172A3[];
extern s8 D_800173E4[];
extern s8 D_80017501[];

extern s32 count_listed_enabled_records(void);
extern void func_8001E578(s32);
extern s32 func_8001E670(s32);
extern s32 func_8001E82C(void);

/* Pick the next town dialogue line from the progress flags and money, marking each line seen as it is used. */
s8 *select_next_dialogue_line(void) {
    s32 initial;
    s32 state_one;
    s32 state_five;
    s32 state_zero;
    s32 value;

    initial = 0;
    if (func_8001E670(Ft_home01_rees_once) == 0) {
        func_8001E578(Ft_home01_rees_once);
    } else {
        initial = 1;
    }

    if (func_8001E670(initial) == 0 && func_8001E82C() != 0) {
        if (func_8001E82C() >= 5) {
            if (func_8001E670(Ftt_fkoya_isaku_scene00_first) == 0) {
                if (func_8001E670(F_ie_huusya_no_sasoi_once) == 0) {
                    func_8001E578(F_ie_huusya_no_sasoi_once);
                    return D_80017152;
                }
                return D_800172A3;
            }
        }

        if (func_8001E670(Ftt_fkoya_isaku_scene01_ok) != 0) {
            if (func_8001E670(F_sbs13_pad04) == 0) {
                if (func_8001E670(F_sbs13_pad02) == 0) {
                    if (func_8001E670(F_ie_pool_no_sasoi_once) == 0) {
                        func_8001E578(F_ie_pool_no_sasoi_once);
                        return D_800173E4;
                    }
                    return D_80017501;
                }
            }
        }

        if ((u32)*(s32 *)((u8 *)*(void **)((u8 *)town_scene_root + 0x38) + 0x2D68) >= 10000U) {
            if (func_8001E670(F_sb22_goods_first) == 0) {
                return D_800164CC;
            }
        }

        {
            Rec_D_80016000 *root;

            root = town_scene_root;
            if ((u32)*(s32 *)((u8 *)root->town_state + 0x2D68) >= 20000U) {
                if ((root->services->callback_2D4)(0) == 0) {
                    return D_8001688A;
                }
            }
        }

        value = (*(StateQuery *)((u8 *)*(void **)((u8 *)town_scene_root + 0x20) + 0x2D4))(0);
        if (value > 0) {
            u8 *town = *(u8 **)((u8 *)town_scene_root + 0x38);
            if (town[0x33A8] != 0x12 && town[0x33A9] != 0x12) {
                if (func_8001E670(F_ie_otera_no_sasoi_once) == 0) {
                    func_8001E578(F_ie_otera_no_sasoi_once);
                    return D_80016E0C;
                }
            }
        }

        {
            TownEventState *state;

            state = town_event_state;
            state_zero = state->unk_00;
            if (state_zero == 2) {
                state_five = state->selection_mode;
                if (state_five == state_zero) {
                    state_one = state->dispatchState;
                    if (state_one == 1) {
                        if ((*(StateQuery *)((u8 *)*(void **)((u8 *)town_scene_root + 0x20) + 0x2D4))(0) == state_five) {
                            if (count_listed_enabled_records() >= 3) {
                                return D_80016D77;
                            }
                            if (count_listed_enabled_records() == state_one) {
                                {
                                    TownEventState *phase;

                                    phase = town_event_state;
                                    value = phase->selected_entry;
                                }
                                if (value == state_one) {
                                    return D_80016BCF;
                                }
                                if (value == state_five) {
                                    return D_80016C77;
                                }
                                if (value == 3) {
                                    return D_80016C24;
                                }
                                if (value == 6) {
                                    return D_80016CCE;
                                }
                            }
                        } else {
                            {
                                TownEventState *phase;

                                phase = town_event_state;
                                value = phase->selected_entry;
                            }
                            if (value == state_one) {
                                return D_80016BCF;
                            }
                            if (value == state_five) {
                                return D_80016C77;
                            }
                            if (value == 3) {
                                return D_80016C24;
                            }
                            if (value == 6) {
                                return D_80016CCE;
                            }
                        }
                    }
                }
            }
        }
    }

    if (func_8001E670(sn_mam_pan_give) != 0) {
        return D_80016359;
    }
    return D_8001602A;
}
