#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


extern s32 func_800197FC(s32 expected_second, s32 expected_first);
void func_8001A554(s32);
void func_8001A5CC(s32);
extern s32 func_8001A64C(s32 flagIndex);
extern s32 D_8002116C;


/* Processes event conditions and returns the corresponding data pointer, or null. */
void *get_local_global_table(void) {
    if (func_800197FC(0xD, 6) != 0) {
        town_scene_root->services->callback_078(0);
        func_8001A554(F_sbs32_pad02);
        func_8001A554(F_sbs32_pad03);
        func_8001A554(F_sbs32_pad04);
        func_8001A554(F_sbs32_pad05);
        func_8001A554(F_sbs32_pad06);
        func_8001A5CC(F_sbs32_pad25);
        return &D_8002116C;
    }
    if (func_8001A64C(F_sbs32_pad06) != 0) {
        return (s32 *)((s8 *)&D_8002116C + 0x21A);
    }
    return 0;
}
