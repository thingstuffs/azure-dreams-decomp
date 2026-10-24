#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern s32 town_table_contains_first_byte(s32);

typedef void (*TownCallback)(s32, s32);

/* Checks town event conditions and invokes the town callback if they allow it. */
s32 check_town_event_town_callback(void) {
    s8 *callback_object;

    set_script_flag_94c();
    if (town_table_contains_first_byte(0xB) != 0) {
        func_8001A554(F_sbs32_pad17);
    }

    if ((func_8001A64C(F_sbs32_pad32) == 0) ||
        ((func_8001A64C(F_sbs32_pad30) != 0) && (func_8001A64C(F_sbs32_pad17) != 0))) {
        func_8001A554(F_sbs32_pad29);
        return 1;
    }

    callback_object = *(s8 **)(*(s8 **)((s8 *)(&town_scene_root)) + 0x20);
    (*(TownCallback *)(callback_object + 0x2F8))(0xF, 0x200);
    return 0;
}
