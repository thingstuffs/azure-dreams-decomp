#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
extern u8 D_8001D7A0[];
extern u8 D_8001D6B0[];

typedef s32 (*Callback)(s32, s32);

extern s32 func_8001991C(s32, void *);
extern void func_80019988(void); /* this scene's placed copy of set_current_entry_script_flag */
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);

/* Advance the town scene: finish early on flag 0x1068, else arm the 0x949/0x94A record or run the step check, then hand back to the scene callback. */
s32 advance_town_scene_finish_early(s32 kind, void *param)
{
    set_script_flag_94c();
    if (func_8001A64C(Frg_vivian_fine) != 0) {
        func_8001A554(F_sbs32_pad37);
        func_8001A554(F_sbs32_pad20);
        return 1;
    }

    if (func_8001A64C(F_sbs32_pad31) == 0) {
        if (func_8001A64C(F_sbs32_pad32) != 0) {
            void *ptr;

            func_8001A554(F_sbs32_pad31);
            ptr = *(void **)((u8 *)(&town_scene_root));
            ptr = *(void **)((s8 *)ptr + 0x1C);
            *(void **)((s8 *)ptr + 0x40) = (s8 *)D_8001D6B0;
        } else {
            void *ptr;

            func_8001A554(F_sbs32_pad31);
            ptr = *(void **)((u8 *)(&town_scene_root));
            ptr = *(void **)((s8 *)ptr + 0x1C);
            *(void **)((s8 *)ptr + 0x40) = (s8 *)D_8001D7A0;
        }
    } else {
        func_80019988();
        if (func_8001991C(kind, param) != 0) {
            return 1;
        }
    }
    {
        void *ptr;
        s32 first_arg;

        ptr = *(void **)((u8 *)(&town_scene_root));
        ptr = *(void **)((s8 *)ptr + 0x20);
        first_arg = 0xF;
        ptr = *(void **)((s8 *)ptr + 0x2F8);
        ((Callback)ptr)(first_arg, 0x200);
    }
    return 0;
}

/* MECHANISM: Recovering 800183C4/800183EC as local joins removed phantom calls and the s2 hold,
   yielding the retail 0x20/s0-s1-ra prologue. */
