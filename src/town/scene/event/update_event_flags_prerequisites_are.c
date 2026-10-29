#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/event.h"

extern s32 func_8001A554(s32 flag_id);
extern s32 func_8001A64C(s32 flag_id);
extern s32 town_table_contains_first_byte(s32 value);

/* Update event flags when prerequisites are met, otherwise invoke the fallback callback. */
s32 update_event_flags_prerequisites_are(void) {
    set_script_flag_94c();
    if (town_table_contains_first_byte(6) != 0) {
        func_8001A554(F_sbs32_pad16);
    }
    if (town_table_contains_first_byte(0xB) != 0) {
        func_8001A554(F_sbs32_pad17);
    }
    if (func_8001A64C(F_sbs32_pad16) != 0 && func_8001A64C(F_sbs32_pad32) != 0) {
        func_8001A554(F_sbs32_pad18);
        return 1;
    }
    if (func_8001A64C(F_sbs32_pad17) != 0 && func_8001A64C(F_sbs32_pad30) != 0) {
        func_8001A554(F_sbs32_pad18);
        func_8001A554(F_sbs32_pad28);
        func_8001A554(F_sbs32_pad29);
        return 1;
    }
    {
        s8 *context = *(s8 **)((u8 *)(&town_scene_root));
        s8 *callback_table = *(s8 **)(context + 0x20);
        s32 (*fallback_fn)(s32, s32) = *(s32 (**)(s32, s32))(callback_table + 0x2F8);
        fallback_fn(0xF, 0x200);
    }
    return 0;
}
