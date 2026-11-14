#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"
extern u8 D_8001D7A0[];
extern u8 D_8001D6B0[];

typedef s32 (*Callback)(s32, s32);

extern void func_80019988(void); /* this scene's placed copy of set_current_entry_script_flag */

/* Advance the town scene: finish early on flag 0x1068, else arm the 0x949/0x94A record or run the step check, then hand back to the scene callback. */
s32 advance_town_scene_finish_early(s32 kind, void *param)
{
    set_script_flag_sbs32_pad34();
    if (get_script_flag_mask(Frg_vivian_fine) != 0) {
        set_script_flag_bit(F_sbs32_pad37);
        set_script_flag_bit(F_sbs32_pad20);
        return 1;
    }

    if (get_script_flag_mask(F_sbs32_pad31) == 0) {
        if (get_script_flag_mask(F_sbs32_pad32) != 0) {
            void *ptr;

            set_script_flag_bit(F_sbs32_pad31);
            ptr = (void *)town_scene_root;
            ptr = *(void **)((s8 *)ptr + 0x1C);
            *(void **)((s8 *)ptr + 0x40) = (s8 *)D_8001D6B0;
        } else {
            void *ptr;

            set_script_flag_bit(F_sbs32_pad31);
            ptr = (void *)town_scene_root;
            ptr = *(void **)((s8 *)ptr + 0x1C);
            *(void **)((s8 *)ptr + 0x40) = (s8 *)D_8001D7A0;
        }
    } else {
        func_80019988();
        if (apply_selected_entry_values(kind, param) != 0) {
            return 1;
        }
    }
    {
        void *ptr;
        s32 first_arg;

        ptr = (void *)town_scene_root;
        ptr = *(void **)((s8 *)ptr + 0x20);
        first_arg = 0xF;
        ptr = *(void **)((s8 *)ptr + 0x2F8);
        ((Callback)ptr)(first_arg, 0x200);
    }
    return 0;
}

/* MECHANISM: Recovering 800183C4/800183EC as local joins removed phantom calls and the s2 hold,
   yielding the retail 0x20/s0-s1-ra prologue. */
